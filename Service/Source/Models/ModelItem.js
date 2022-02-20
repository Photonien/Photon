const Mongoose = require("mongoose");
const Schema = Mongoose.Schema;

const ItemSchema = new Schema({
    Id: {type: String, required: true},
    Author: { type: String, required: true},
    Content: { type: Schema.Types.Mixed, required: true}
}, { timestamps: true });

const Item = Mongoose.model("Item", ItemSchema);

module.exports = Item;