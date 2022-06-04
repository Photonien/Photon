// use tide::prelude::*;
use tide::Request;

// #[derive(Debug, Deserialize)]
// struct Animal {
//     name: String,
//     legs: u16,
// }

pub async fn route_main(mut _req: Request<()>) -> tide::Result {
    Ok(format!("Hello, ! I've put in an order for shoes").into())
}
