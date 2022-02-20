var express = require("express");
const crypto = require('crypto-js');
var router = express.Router();

const UserModel = require("../Models/ModelUser");

router.post("/login", (req, res) => {
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

router.get("/logout", (req, res) => {
    req.session.destroy();
    res.status(200).json({ Message: "Log out is successfull"});
});

module.exports = router;