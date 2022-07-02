use tide::Body;
use tide::prelude::*;
use tide::Request;
use tide::Response;
use tide::Server;

#[derive(Debug, Deserialize, Serialize)]
struct Folder {
    id: u32,
    name: String,
    parent: u16,
}

pub async fn route_users_get(mut _req: Request<()>) -> tide::Result {
    let mut res = Response::new(200);

    res.set_body(Body::from_string("Hello, world!".to_string()));

    Ok(res)
}