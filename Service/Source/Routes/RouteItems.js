var express = require("express");
const crypto = require('crypto-js');
var router = express.Router();

const ItemModel = require("../Models/ModelItem");

router.get("/", (req, res) => {
    ItemModel.find({})
        .then((result) => {
            res.status(200).json(result)
        })
        .catch((err) => {
            res.status(500).json(err)
        });
});

router.post("/new", (req, res) => {
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

module.exports = router;
