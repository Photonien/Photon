const express = require("express");
const bodyParser = require("body-parser");
const Mongoose = require("mongoose");
const cors = require("cors");
const redis = require('redis');
const crypto = require('crypto-js');
const sessions = require('express-session');

// Models

const UserModel = require("./ModelUser");
const ItemModel = require("./ModelItem");

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

// Authentication Process

expressApp.post("/users/new", (req, res) => {
    var username = req.body.Username;
    var password = req.body.Password;
    var passwordEncrypted = crypto.MD5(password);
    passwordEncrypted = passwordEncrypted.toString();

    var session = req.session;

    console.log("Registering with " + username + ", " + passwordEncrypted);

    UserModel
    .findOne({Username: username})
    .then((result) => {
        if(result == null)
        {
            const newUserModel = new UserModel({
                Username: username,
                Password: passwordEncrypted
            });

            newUserModel
                .save()
                .then((result) => {
                    res.status(200).json(result)
                })
                .catch((err) => {
                    res.status(400).json(err)
                });
        }
        else
        {
            res.status(200).json({ Message: result.Username + " is already exits"});
        }
        
    })
    .catch((err) => {
        res.status(400).json(err)
    });

});

expressApp.post("/auth/login", (req, res) => {
    var username = req.body.Username;
    var password = req.body.Password;
    var passwordEncrypted = crypto.MD5(password);
    passwordEncrypted = passwordEncrypted.toString();

    console.log("Trying to login  with " + username + ", " + passwordEncrypted);

    var sessionUsername = req.session.username;
    if(!sessionUsername)
    {
        UserModel
            .findOne({ Username: username, Password: passwordEncrypted })
            .then((result) => {
                if(result != null)
                {
                    req.session.username = result.Username;
                    res.status(200).json({ Message: "Log on with " + result.Username});
                }
                else
                {
                    res.status(200).json({ Message: "User is not found!"})
                }
                
            })
            .catch((err) => {
                res.status(500).json(err)
            });
    }
    else
    {
        res.status(500).json({ Message: "Already log on with " + sessionUsername})
    } 
});

expressApp.get("/users/delete/all", (req, res) => {
    UserModel.remove({}, (result) =>
    {
        req.session.destroy();
        res.status(200).json({ Message: "All users are removed"});
    });
});

expressApp.get("/users", (req, res) => {
    UserModel.find({})
        .then((result) => {
            res.status(200).json(result)
        })
        .catch((err) => {
            res.status(500).json(err)
        });
});

expressApp.get("/auth/logout", (req, res) => {
    req.session.destroy();
    res.status(200).json({ Message: "Log out is successfull"});
});

expressApp.post("/items/new", (req, res) => {
    var author = req.body.Author;
    var content = req.body.Content;

    console.log("New item with " + author + ", " + content);

    const newItemModel = new ItemModel({
        Author: author,
        Id: "123",
        Content: content
    });

    newItemModel
        .save()
        .then((result) => {
            res.status(200).json(result)
        })
        .catch((err) => {
            res.status(400).json(err)
        });

});

expressApp.get("/items", (req, res) => {
    ItemModel.find({})
        .then((result) => {
            res.status(200).json(result)
        })
        .catch((err) => {
            res.status(500).json(err)
        });
});

expressApp.listen(expressPort, async () => {
    console.log("Backend is listening to port {PORT}")
    console.log(`Backend is connecting to MongoDb`);

    await Mongoose.connect("mongodb://mongo:27017/Photon", {
        useNewUrlParser: true,
        useUnifiedTopology: true,
    });

    console.log("Backend connected to MongoDb!");
});