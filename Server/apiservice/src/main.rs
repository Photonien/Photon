use std::error::Error;
// use tide::prelude::*;
// use tide::Request;
use tokio;

pub mod connection_mongodb;
pub mod routes;

use crate::connection_mongodb::connection;
use crate::routes::main::route_main;

static LISTENER: &str = "127.0.0.1:8080";

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    unsafe {
        let result = connection().await;

        if result? {
            println!("Database connection is established!");
        } else {
            println!("Database connection is NOT established!");
        }
    }

    println!("Api is listening on {}", LISTENER);

    let mut app = tide::new();
    app.at("/").get(route_main);
    app.listen(LISTENER).await?;
    Ok(())
}
