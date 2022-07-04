use sqlx::postgres::PgRow;
use sqlx::postgres::Postgres;
use sqlx::Acquire;
use sqlx::Row;
use sqlx::{Error, FromRow};
use tide::prelude::*;
use tide::Body;
use tide::Request;
use tide::Response;

#[allow(unused_imports)]
use tide_sqlx::SQLxRequestExt;
#[warn(unused_imports)]

#[derive(Debug, Deserialize, Serialize)]
struct Folder {
    id: i32,
    name: String,
    parent: Option<i32>,
}

impl<'r> FromRow<'r, PgRow> for Folder {
    fn from_row(row: &'r PgRow) -> Result<Self, Error> {
        let id = row.try_get("id")?;
        let name = row.try_get("name")?;
        let mut parent = None;

        if let Ok(found_parent) = row.try_get("parent") {
            parent = found_parent;
        }

        Ok(Folder { id, name, parent })
    }
}

#[derive(Debug, Deserialize, Serialize)]
pub struct Folders {
    folders: Vec<Folder>,
}

impl Folders {
    fn new() -> Folders {
        Folders {
            folders: vec![]
        }
    }

    fn append(&mut self, folder: Folder) {
        self.folders.push(folder);
    }
}

pub async fn get(req: Request<()>) -> tide::Result {
    let mut pg_conn = req.sqlx_conn::<Postgres>().await;

    let rows = sqlx::query("SELECT * FROM folders")
        .fetch_all(pg_conn.acquire().await?)
        .await?;

    let mut response_folders = Folders::new();

    for row in &rows {
        if let Ok(found_folder) = Folder::from_row(&row) {
            response_folders.append(found_folder);
        } else {
            println!("Error!");
        }
    }

    let mut res = Response::new(200);

    res.set_body(Body::from_json(&response_folders)?);
    
    Ok(res)
}