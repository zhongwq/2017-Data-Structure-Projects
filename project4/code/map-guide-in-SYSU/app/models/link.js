// link model

var mongoose = require('mongoose'),
  Schema = mongoose.Schema;

var linkSchema = new Schema({
  source: { type: String, required: true },
  target: { type: String, required: true },
  value: { type: Number, required: true },
  type: { type: Number, required: true }
});

mongoose.model('Link', linkSchema);
