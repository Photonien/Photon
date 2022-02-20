const express = require("express");
const bodyParser = require("body-parser");
const Mongoose = require("mongoose");
const cors = require("cors");
const redis = require('redis');
const crypto = require('crypto-js');
const sessions = require('express-session');

// Models

const UserModel = require("./Models/ModelUser");
const ItemModel = require("./Models/ModelItem");
const CollectionModel = require("./Models/ModelCollection");

var RouteAuth = require("./Routes/Auth");
var RouteUsers = require("./Routes/Users");
var RouteCollections = require("./Routes/Collections");
var RouteItems = require("./Routes/Items");

// Globals

const SecretKey = "thisismysecrctekeyfhrgfgrfrty84fwir767";

const expressPort = process.env.PORT || 6000;
const expressApp = express();

expressApp.use(express.json());
expressApp.use(express.urlencoded({ extended: true }));
expressApp.use(cors());

expressApp.use(sessions({
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

expressApp.get('/', function (req, res) {
    res.send({ Message: "Welcome to API!"});
});

expressApp.use("/auth", RouteAuth);
expressApp.use("/users", RouteUsers);
expressApp.use("/collections", RouteCollections);
expressApp.use("/items", RouteItems);

expressApp.listen(expressPort, async () => {
    console.log(`Backend is listening to port ${expressPort}`)
    console.log(`Backend is connecting to MongoDb`);

    await Mongoose.connect("mongodb://mongo:27017/Photon", {
        useNewUrlParser: true,
        useUnifiedTopology: true,
    });

    console.log("Backend connected to MongoDb!");
});