/**
 * Created by zhongwq on 2017/12/19.
 */
// user model

var mongoose = require('mongoose'),
  Schema = mongoose.Schema
bcrypt = require('bcrypt'),
  SALT_WORK_FACTOR = 10;

var userSchema = new Schema({
  username: { type: String, required: true },
  password: { type: String, required: true }
});

userSchema.pre('save', function(next) {
  var user = this;
  if (!user.isModified('password'))
    return next();
  bcrypt.genSalt(SALT_WORK_FACTOR, function(err, salt) {
    if (err) return next(err);
    bcrypt.hash(user.password, salt, function(err, hash) {
      if (err) return next(err);
      user.password = hash;
      next();
    });
  });
});//使用bcrypt作为中间件加密密码

userSchema.methods.comparePassword = function(candidatePassword, result) {
  bcrypt.compare(candidatePassword, this.password, function(err, isMatch) {
    if (err) return result(err);
    result(null, isMatch);
  });
};

mongoose.model('User', userSchema);
