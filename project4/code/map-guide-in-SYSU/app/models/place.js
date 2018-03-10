// place model

var mongoose = require('mongoose'),
  Schema = mongoose.Schema;

var placeSchema = new Schema({
  name: { type: String, required: true },
  value: { type: String, required: true },
  introduce: { type: String, required: true },
  x: { type: Number, required: true },
  y: { type: Number, required: true },
  meta: { type: Schema.Types.Mixed },
  point: { type: Number, required: true },
  comments: [ Schema.Types.Mixed ]
});

mongoose.model('Place', placeSchema);
