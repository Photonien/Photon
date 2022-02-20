var express = require("express");
const crypto = require('crypto-js');
var router = express.Router();

const ItemModel = require("../Models/ModelItem");

router.get("/", (req, res) => {
    res.send({ Message: "Welcome to API!"});
});

module.exports = router;
