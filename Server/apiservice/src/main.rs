use mongodb::{Client, options::{ClientOptions, ResolverConfig}, bson::doc};
use std::{error::Error};
use tokio;
use chrono::{TimeZone, Utc};

#[macro_use] extern crate rocket;

#[get("/")]
fn index() -> &'static str {
    "Hello, world!"
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    let client_uri = "mongodb://localhost:27017";

    let options =
        ClientOptions::parse_with_resolver_config(&client_uri, ResolverConfig::cloudflare())
        .await?;

    let client = Client::with_options(options)?;

    let new_doc = doc! {
    "title": "Parasite",
    "year": 2020,
    "plot": "A poor family, the Kims, con their way into becoming the servants of a rich family, the Parks. But their easy life gets complicated when their deception is threatened with exposure.",
    "released": Utc.ymd(2020, 2, 7).and_hms(0, 0, 0),
    };

    let movies = client.database("sample_mflix").collection("movies");

    let insert_result = movies.insert_one(new_doc.clone(), None).await?;

    println!("New document ID: {}", insert_result.inserted_id);

    let _rocket = rocket::build()
        .mount("/hello", routes![index])
        .launch()
        .await?;

    Ok(())
}