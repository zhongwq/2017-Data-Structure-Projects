var express = require('express'),
  router = express.Router(),
  mongoose = require('mongoose'),
  Post = mongoose.model('Post'),
  User = mongoose.model('User');

module.exports = function (app) {
  app.use('/', router);
};

router.get('/', function (req, res, next) {
  res.render('map', {
    title: "Sysu Map"
  });
});

router.get('/blog', function(req, res, next) {
  Post.find({}, function(err, posts) {
    res.render('blog', {
      title: "Sysu Map Blog",
      posts: posts
    });
  });
});

router.get('/admin/signin', function(req, res, next) {
  res.render('admin/signin', { title: '登陆' });
});

router.get('/admin/signup', function(req, res, next) {
  res.render('admin/signup', { title: '注册管理账号' });
});


router.post('/admin/signin', function(req, res, next) {
  var signinData = req.body;
  var error = [];
  User.findOne({username: signinData.username}, function(err, user) {
    if (err) {
      console.log(err);
      error.push("Something wrong with the server! Please try after serveral minutes!");
      return showErrInPage(res, 'admin/signin', { title: '登陆' }, error);
    }
    if (!user) {
      console.log("No user");
      error.push("The account is not exist!");
      return showErrInPage(res, 'admin/signin', { title: '登陆' }, error);
    }
    user.comparePassword(signinData.password, function(err, isMatch) {
      if (err) {
        console.log(err);
        error.push("Something wrong with the server! Please try after serveral minutes!");
        return showErrInPage(res, 'admin/signin', { title: '登陆' }, error);
      }
      if (isMatch) {
        req.session.user = user;
        res.redirect('/admin');
      } else {
        error.push("The password is not match!");
        return showErrInPage(res, 'admin/signin', { title: '登陆' }, error);
      }
    });
  });
});

router.post('/admin/signup', function(req, res, next) {
  var userData = req.body;
  var error = [];
  if (!/^[a-zA-Z][a-zA-Z0-9_]{5,17}$/.test(userData.username))
    error.push("用户名首位为字母,中间为下划线、数字或字母,长度为6-18");
  if (!userData.password.length >= 6)
    error.push("密码必须大于等于6位");
  if (error.length > 0)
    return showErrInPage(res, 'admin/signup', { title: '注册管理账号', user: userData}, error);
  User.find({}, function(err, users) {
    if (err) {
      console.log(err);
      error.push("Something wrong with the server! Please try after serveral minutes!");
      return showErrInPage(res, 'admin/signup', { title: '注册管理账号', user: userData}, error);
    }
    for (var key in userData) {
      if (key === "username") {
        if (!!users[userData.username])
          error.push("The username is Repeated!");
        continue;
      }
      for (var user in users) {
        if (users.hasOwnProperty(user) && users[user][key] == userData[key]) {
          error.push("The " + key + " is Repeated!");
        }
      }
    }
    if (error.length > 0) {
      return showErrInPage(res, 'admin/signup', { title: '注册管理账号', user: userData}, error);
    } else {
      var user = new User({
        username: userData.username,
        password: userData.password
      });
      user.save(function(err, user) {
        if (err) {
          console.log(err);
          error.push("Something wrong with the server! Please try after serveral minutes!");
          return showErrInPage(res, 'admin/signup', { title: '注册管理账号', user: userData}, error);
        }
        req.session.user = user;
      });
      res.redirect('/admin');
    }
  });
});

router.all('*', function(req, res, next) {
  req.session.user ? next(): res.redirect('/admin/signin');
});

router.get('/admin/logout', function(req, res, next) {
  delete req.session.user;
  res.redirect('/signin');
});

router.get('/admin', function (req, res, next) {
  res.render('admin/index', {
    title: "Sysu Map Manager"
  });
});

function showErrInPage(res, page, data, error) {
  var errorHtml = "";
  for (var i = 0; i < error.length; i++){
    var err = "<div class=\"error\"><div class=\"msg\">"+error[i]+"</div><div class=\"close\">X</div></div>";
    errorHtml += err;
  }
  data.error = errorHtml;
  res.render(page, data);
}
