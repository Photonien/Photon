const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const UserSchema = new Schema({
    Username: { type: String, required: true},
    Password: { type: String, required: true}
}, { timestamps: true });

const User = Mongoose.model("User", UserSchema);

module.exports = User;