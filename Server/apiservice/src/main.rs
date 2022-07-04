use sqlx::postgres::Postgres;
use std::error::Error;
use tide_sqlx::SQLxMiddleware;

#[allow(unused_imports)]
use tide_sqlx::SQLxRequestExt;
#[warn(unused_imports)]


pub mod routes;

static LISTENER: &str = "127.0.0.1:8080";

#[async_std::main]
async fn main() -> Result<(), Box<dyn Error>> {
    println!("Api is listening on {}", LISTENER);

    let mut app = tide::new();

    app.with(
        SQLxMiddleware::<Postgres>::new("postgres://devuser:devuser@127.0.0.1:5432/postgres")
            .await?,
    );

    app.at("/").get(routes::main::get);

    app.at("/users").get(routes::users::get);

    app.at("/users/:id").get(routes::users::get_by_id);

    app.at("/users").post(routes::users::post);

    app.at("/modules").get(routes::modules::get);

    app.at("/folders").get(routes::folders::get);

    app.listen(LISTENER).await?;

    Ok(())
}
