const express = require("express");
const bodyParser = require("body-parser");
const mongoose = require("mongoose");
const cors = require("cors");
const redis = require('redis');
const crypto = require('crypto-js');
const sessions = require('express-session');

var RouteAuth = require("./Routes/RouteAuth");
var RouteUsers = require("./Routes/RouteUsers");
var RouteCollections = require("./Routes/RouteCollections");
var RouteItems = require("./Routes/RouteItems");

// Globals

const SecretKey = "thisismysecrctekeyfhrgfgrfrty84fwir767";

const appPort = process.env.PORT || 6000;
const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cors());

app.use(sessions({
    secret: SecretKey,
    saveUninitialized:true,
    resave: false
}));

const clientRedis = redis.createClient(6379, "redis");

clientRedis.on("error", error => {
    console.error(error);
});

clientRedis.on('connect', function () {
    console.log('Backend connected to Redis server!');
});

app.get('/', function (req, res) {
    res.send({ Message: "Welcome to API!"});
});

app.use("/auth", RouteAuth);
app.use("/users", RouteUsers);
app.use("/collections", RouteCollections);
app.use("/items", RouteItems);

app.listen(appPort, async () => {
    console.log(`Backend is listening to port ${appPort}`)
    console.log(`Backend is connecting to MongoDb`);

    await mongoose.connect("mongodb://mongo:27017/Photon", {
        useNewUrlParser: true,
        useUnifiedTopology: true,
    });

    console.log("Backend connected to MongoDb!");
});