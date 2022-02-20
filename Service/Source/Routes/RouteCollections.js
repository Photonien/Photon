var express = require("express");
const crypto = require('crypto-js');
var router = express.Router();

const CollectionModel = require("../Models/ModelCollection");

router.get("/", (req, res) => {
    CollectionModel.find({})
        .then((result) => {
            res.status(200).json(result)
        })
        .catch((err) => {
            res.status(500).json(err)
        });
});

router.post("/new", (req, res) => {
    var author = req.body.Author;
    var name = req.body.Name;
    var parent = req.body.Parent;
    var childs = req.body.Childs;

    console.log("New collection with " + name);

    const newCollectionModel = new CollectionModel({
        Author: author,
        Name: name,
        Parent: parent
    });

    newCollectionModel
        .save()
        .then((result) => {
            res.status(200).json(result)
        })
        .catch((err) => {
            res.status(400).json(err)
        });

});


module.exports = router;