use std::error::Error;
use tide::prelude::*;
use tide::Request;
use sqlx::Acquire;
use sqlx::postgres::Postgres;
use tide_sqlx::SQLxMiddleware;
use tide_sqlx::SQLxRequestExt;

pub mod routes;

use crate::routes::main::route_main;
use crate::routes::users::route_users_get;
use crate::routes::users::route_users_get_by_id;
use crate::routes::users::route_users_post;

static LISTENER: &str = "127.0.0.1:8080";

#[async_std::main]
async fn main() -> Result<(), Box<dyn Error>> {
    println!("Api is listening on {}", LISTENER);

    let mut app = tide::new();

    app.with(SQLxMiddleware::<Postgres>::new("postgres://devuser:devuser@127.0.0.1:5432/postgres").await?);


    app.at("/").get(route_main);
    app.at("/users").get(route_users_get);
    app.at("/users/:id").get(route_users_get_by_id);
    app.at("/users").post(route_users_post);
    app.listen(LISTENER).await?;
    Ok(())
}
