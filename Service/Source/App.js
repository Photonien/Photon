const express = require("express");
const bodyParser = require("body-parser");
const mongoose = require("mongoose");
const cors = require("cors");
const redis = require('redis');
const crypto = require('crypto-js');
const sessions = require('express-session');

const app = express();
const clientRedis = redis.createClient(6379, "redis");

// Routes

var RouteIndex = require("./Routes/RouteIndex");
var RouteAuth = require("./Routes/RouteAuth");
var RouteUsers = require("./Routes/RouteUsers");
var RouteCollections = require("./Routes/RouteCollections");
var RouteItems = require("./Routes/RouteItems");

// Globals

const secretKey = "thisismysecrctekeyfhrgfgrfrty84fwir767";
const appPort = process.env.PORT || 6000;

clientRedis.on("error", error => {
    console.error(error);
});

clientRedis.on('connect', function () {
    console.log('Backend connected to Redis server!');
});

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cors());

app.use(sessions({
    secret: secretKey,
    saveUninitialized:true,
    resave: false
}));

app.use("/", RouteIndex);
app.use("/auth", RouteAuth);
app.use("/users", RouteUsers);
app.use("/collections", RouteCollections);
app.use("/items", RouteItems);

app.listen(appPort, async () => {
    console.log(`Backend is listening to port ${appPort}`);

    await mongoose.connect("mongodb://mongo:27017/Photon", {
        useNewUrlParser: true,
        useUnifiedTopology: true,
    }).finally(() => {
        console.log("Backend connected to MongoDb server!");
    });

});