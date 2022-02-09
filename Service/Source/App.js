const express = require("express");
const bodyParser = require("body-parser");
const { TodoModel } = require("./Model");
const Mongoose = require("mongoose");
const cors = require("cors");
const redis = require('redis');

const expressPort = process.env.PORT || 6000;
const expressApp = express();

expressApp.use(express.json());
expressApp.use(express.urlencoded({ extended: true }));
expressApp.use(cors());

const clientRedis = redis.createClient(6379, "redis");

clientRedis.on("error", error => {
    console.error(error);
});

clientRedis.on('connect', function () {
    console.log('Backend connected to Redis server!');
});

expressApp.get('/', function (req, res) {
    res.send('hello world');
});

expressApp.get("/listtodo", (req, res) => {
    TodoModel.find({})
        .then((todoList) => res.status(200).json(todoList))
        .catch((e) => res.status(500).json(e));
});

expressApp.get("/listlogin", (req, res) => {
    clientRedis.get('login', function (err, reply) {
        console.log(reply);
        res.status(200).send("Successful");
    });
});

expressApp.post("/newtodo", (req, res) => {
    const todo = new TodoModel({
        ...req.body,
        created_at: new Date(),
    });

    todo
        .save()
        .then((savedTodo) => res.status(200).json(savedTodo))
        .catch((e) => res.status(400).json(e));
});

expressApp.post("/newlogin", (req, res) => {
    clientRedis.set('login', 'asdasdasdas', (errr, reply) => {
        console.log(reply);
        res.status(200).send("Successful");
    });

});

expressApp.listen(expressPort, async () => {
    console.log("Backend is listening to port {PORT}")
    console.log(`Backend is connecting to MongoDb`);

    await Mongoose.connect("mongodb://mongo:27017/todo", {
        useNewUrlParser: true,
        useUnifiedTopology: true,
    });

    console.log("Backend connected to MongoDb!");
});