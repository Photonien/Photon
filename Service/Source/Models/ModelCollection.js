const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const CollectionSchema = new Schema({
    Name: { type: String, required: true},
    Parent: { type: String, required: false},
    Childs: [{ type: String, required: false}]
}, { timestamps: true });

const Collection = Mongoose.model("Collection", CollectionSchema);

module.exports = Collection;