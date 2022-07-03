use sqlx::Column;
use sqlx::Row;
use tide::Body;
use tide::prelude::*;
use tide::Request;
use tide::Response;
use sqlx::Acquire;
use sqlx::postgres::Postgres;
use tide_sqlx::SQLxRequestExt;

#[derive(Debug, Deserialize, Serialize)]
struct Api {
    version: String
}

use sqlx::{FromRow, Error};
use sqlx::postgres::PgRow;

pub struct Modules {
    id: i32,
    name: String,
    parent: i32
}

impl<'r> FromRow<'r, PgRow> for Modules {
    fn from_row(row: &'r PgRow) -> Result<Self, Error> {
        let id = row.try_get("id")?;
        let name = row.try_get("name")?;
        let parent = row.try_get("parent")?;
        Ok(Modules{ id, name, parent })
    }
}

pub async fn route_main(mut req: Request<()>) -> tide::Result {
    let mut pg_conn = req.sqlx_conn::<Postgres>().await;

    let modules = 
        sqlx::query("SELECT * FROM modules")
        .fetch_all(pg_conn.acquire().await?).await?;

    // let user = req.body_json().await?;

    println!("--------------");

   modules[0].columns().iter().for_each(|column| {
    println!("{}, ", column.name());
   });

    modules.iter().for_each(|module| {
        if let Ok(got_module) = Modules::from_row(&module) {
            println!("Module: {}, {}, {}", got_module.id, got_module.name, got_module.parent);
        }
        else
        {
            println!("Errorororo!");
        }
    });

    let api = Api {
        version: "1.0.1".to_string()
    };

    let mut res = Response::new(201);

    res.set_body(Body::from_json(&api)?);

    Ok(res)
}
