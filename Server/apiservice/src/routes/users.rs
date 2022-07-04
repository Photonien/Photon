use tide::Body;
use tide::prelude::*;
use tide::Request;
use tide::Response;

#[derive(Debug, Deserialize, Serialize)]
struct User {
    id: u32,
    username: String,
    password: u16,
}

pub async fn get(mut _req: Request<()>) -> tide::Result {
    let mut res = Response::new(200);

    res.set_body(Body::from_string("Hello, world!".to_string()));

    Ok(res)
}

pub async fn get_by_id(req: Request<()>) -> tide::Result {
    let id = req.param("id")?;

    let user = User {
        id: id.parse::<u32>()?,
        username: "test".to_string(),
        password: 123,
    };

    let mut res = Response::new(200);
    
    res.set_body(Body::from_json(&user)?);

    Ok(res)
}

pub async fn post(mut _req: Request<()>) -> tide::Result {
    let mut res = Response::new(200);

    res.set_body(Body::from_string("Hello, world!".to_string()));

    Ok(res)
}


