use chrono::{TimeZone, Utc};
use mongodb::{
    bson::doc,
    options::{ClientOptions, ResolverConfig},
    Client,
};
use std::error::Error;

static CLIENT_URI: &str = "mongodb://localhost:27015";
static mut CLIENT: Option<Client> = None;

pub async unsafe fn connection() -> Result<bool, Box<dyn Error>> {
    let options =
        ClientOptions::parse_with_resolver_config(&CLIENT_URI, ResolverConfig::cloudflare())
            .await?;

    CLIENT = Some(Client::with_options(options).unwrap());

    let released_date = Utc.ymd(2020, 2, 7).and_hms(0, 0, 0);

    let new_doc = doc! {
    "title": "Parasite",
    "year": 2020,
    "plot": "Test",
    "released": released_date,
    };

    let movies_database = CLIENT.as_ref().unwrap().database("sample_mflix");

    let ping_check = movies_database.run_command(doc! {"ping": 1}, None).await;

    if ping_check.is_ok() {
        let collection = movies_database.collection("movies");

        let insert_result = collection.insert_one(new_doc.clone(), None).await.unwrap();

        println!("New document ID: {}", insert_result.inserted_id);
        return Ok(true);
    } else {
        println!("Error is occured!");
        return Ok(false);
    }
}
