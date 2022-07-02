use tide::Body;
use tide::prelude::*;
use tide::Request;
use tide::Response;
use tide::Server;


#[derive(Debug, Deserialize, Serialize)]
struct Api {
    version: String
}

pub async fn route_main(mut _req: Request<()>) -> tide::Result {

    // let user = req.body_json().await?;
    let api = Api {
        version: "0.0.0".to_string()
    };

    let mut res = Response::new(201);

    res.set_body(Body::from_json(&api)?);

    Ok(res)
}
