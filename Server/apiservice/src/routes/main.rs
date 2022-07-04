use tide::prelude::*;
use tide::Body;
use tide::Request;
use tide::Response;

#[derive(Debug, Deserialize, Serialize)]
struct Api {
    version: String
}

pub async fn get(mut _req: Request<()>) -> tide::Result {

    let api = Api {
        version: "1.0.1".to_string()
    };

    let mut res = Response::new(201);

    res.set_body(Body::from_json(&api)?);

    Ok(res)
}
