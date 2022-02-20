const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const CollectionSchema = new Schema({
    Name: { type: String, required: true},
    Parent: { type: String, required: true},
    Childs: { type: String, required: true}
}, { timestamps: true });

const Collection = Mongoose.model("Collection", CollectionSchema);

module.exports = Collection;