/**
 * Created by zhongwq on 2017/12/17.
 */
// post model

var mongoose = require('mongoose'),
  Schema = mongoose.Schema;

var postSchema = new Schema({
  title: { type: String, required: true },
  path: {type: String, required: true},
  author: { type: String, required: true },
  content: { type: String, required: true },
  meta: { type: Schema.Types.Mixed },
  comments: [ Schema.Types.Mixed ]
});

mongoose.model('Post', postSchema);

