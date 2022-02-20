var express = require("express");
const crypto = require('crypto-js');
var router = express.Router();

const UserModel = require("../Models/ModelUser");


router.get("/", (req, res) => {
    UserModel.find({})
        .then((result) => {
            res.status(200).json(result)
        })
        .catch((err) => {
            res.status(500).json(err)
        });
});

router.post("/new", (req, res) => {
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

router.get("/delete/all", (req, res) => {
    UserModel.remove({}, (result) =>
    {
        req.session.destroy();
        res.status(200).json({ Message: "All users are removed"});
    });
});

module.exports = router;