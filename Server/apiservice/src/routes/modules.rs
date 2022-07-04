use sqlx::postgres::PgRow;
use sqlx::postgres::Postgres;
use sqlx::Acquire;
use sqlx::Row;
use sqlx::{Error, FromRow};
use tide::prelude::*;
use tide::Body;
use tide::Request;
use tide::Response;
use tide_sqlx::SQLxRequestExt;

#[derive(Debug, Deserialize, Serialize)]
pub struct Module {
    id: i32,
    name: String,
    parent: i32,
}

impl<'r> FromRow<'r, PgRow> for Module {
    fn from_row(row: &'r PgRow) -> Result<Self, Error> {
        let id = row.try_get("id")?;
        let name = row.try_get("name")?;
        let parent = row.try_get("parent")?;
        Ok(Module { id, name, parent })
    }
}

#[derive(Debug, Deserialize, Serialize)]
pub struct Modules {
    modules: Vec<Module>,
}

impl Modules {
    fn new() -> Modules {
        Modules {
            modules: vec![]
        }
    }

    fn append(&mut self, module: Module) {
        self.modules.push(module);
    }
}

pub async fn get(req: Request<()>) -> tide::Result {
    let mut pg_conn = req.sqlx_conn::<Postgres>().await;

    let rows = sqlx::query("SELECT * FROM modules")
        .fetch_all(pg_conn.acquire().await?)
        .await?;

    let mut response_modules = Modules::new();

    for row in &rows {
        if let Ok(found_module) = Module::from_row(&row) {
            response_modules.append(found_module);
        } else {
            println!("Error!");
        }
    }

    let mut res = Response::new(200);

    res.set_body(Body::from_json(&response_modules)?);
    
    Ok(res)
}
