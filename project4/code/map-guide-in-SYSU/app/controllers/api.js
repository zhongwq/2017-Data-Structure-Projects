var express = require('express'),
  router = express.Router(),
  mongoose = require('mongoose'),
  Place = mongoose.model('Place'),
  Link = mongoose.model('Link'),
  Post = mongoose.model('Post');

module.exports = function(app) {
  app.use('/api', router);
};

router.get('/allData/:type', function (req, res, next) {
  Place.find({}, function (err, places) {
    if (err)
      return res.jsonp({
        err: err
      });
    var conditions = {};
    if (req.params.type) {
      if (!(req.params.type == "all")) {
        conditions.type = req.params.type == "footWay"?0:1;
      }
    }
    Link.find(conditions, function (err, links) {
      if (err)
        return res.jsonp({
          err: err
        });
      res.jsonp({
        places: places,
        links: links
      });
    });
  });
});

router.get('/place/favourite/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: 'No post id provided!'});
  }
  var conditions = {};
  try {
    conditions._id = mongoose.Types.ObjectId(req.params.id);
  } catch (err) {
    conditions.name = req.params.id;
  }
  Place.findOne(conditions, function(err, place) {
    if (err) {
      return res.jsonp({err: err});
    }
    place.meta.favourite = place.meta.favourite ? place.meta.favourite+1 : 1;
    place.markModified('meta');
    place.save(function (err, place) {
      res.jsonp(place);
    });
  });
});

router.post('/place/comment/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: 'No id is provided!'});
  }
  if (!req.body.email) {
    return res.jsonp({err: "No email is provided!"});
  }
  if (!req.body.content) {
    return res.jsonp({err: "No content is provided!"});
  }
  if (!req.body.point) {
    return res.jsonp({err: "No point is provided!"});
  }
  var conditions = {};
  try {
    conditions._id = mongoose.Types.ObjectId(req.params.id);
  } catch (err) {
    conditions.name = req.params.id;
  }
  Place.findOne(conditions, function(err, place) {
    if (err) {
      return res.jsonp({err: err});
    }
    var comment = {
      email: req.body.email,
      content: req.body.content
    };
    place.point = (place.point*place.comments.length + req.body.point)/(place.comments.length+1);
    place.comments.unshift(comment);
    place.markModified('point');
    place.markModified('comments');
    place.save(function (err, place) {
      res.jsonp({
        place: place,
        newComment: comment
      });
    });
  });
});

router.post('/link/add', function(req, res, next) {
  if (!req.body.source) {
    return res.jsonp({err: "The link's source is not provided!"});
  }
  if (!req.body.target) {
    return res.jsonp({err: "The link's source is not provided!"});
  }
  if (!req.body.value) {
    return res.jsonp({err: "The link's value is not provided!"});
  }
  if (!req.body.type) {
    return res.jsonp({err: "The link's type is not provided!"});
  }
  Link.find({}, function(err, links) {
    if(err) {
      console.log(err);
      return res.jsonp({err: err});
    }
    var newSource = req.body.source, newTarget = req.body.target, newType = req.body.type;
    for (var i = 0; i < links.length; i++) {
      if (links[i].source == newSource && links[i].target == newTarget && links[i].type == newType) {
        return res.jsonp({err: "The link is exists!!"});
      }
      if (links[i].source == newTarget && links[i].target == newSource && links[i].type == newType) {
        return res.jsonp({err: "The link is exists!!"});
      }
    }
    var link = new Link({
      source: newSource,
      target: newTarget,
      type: newType,
      value: req.body.value
    });
    link.save(function(err, msg) {
      if (err) {
        return res.jsonp({err: err});
      }
      res.jsonp({err: undefined, msg: msg});
    });
  });
});

router.post('/place/add', function(req, res, next) {
  if (!req.body.value) {
    return res.jsonp({err: "The place's name is not provided!"});
  }
  if (!req.body.introduce) {
    return res.jsonp({err: "The place's introduce is not provided!"});
  }
  if (!req.body.x) {
    return res.jsonp({err: "The place's posx is not provided!"});
  }
  if (!req.body.y) {
    return res.jsonp({err: "The place's posy is not provided!"});
  }

  Place.find({}, function(err, places) {
    if (err) {
      console.log(err);
      return res.jsonp({ err: err});
    }
    var placeName = req.body.value;
    for (var i = 0; i < places.length; i++) {
      if (places[i].value == req.body.value) {
        return res.jsonp({err: "The place is exist!"});
      }
      if (places[i].name == req.body.value) {
        placeName = "new" + placeName;
      }
    }
    var place = new Place({
      name: placeName,
      value: req.body.value,
      introduce: req.body.introduce,
      x: req.body.x,
      y: req.body.y,
      meta: {favourite: 0},
      point: 0,
      comments: []
    });

    place.save(function(err, msg) {
      if (err) {
        return res.jsonp({err: err});
      }
      res.jsonp({err: undefined, msg: msg});
    });
  });
});

router.get('/place/delete/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: "No id is provided!"});
  }
  Place.findOne({_id: req.params.id}, function(err, place) {
    if (err)
      return res.jsonp({err: err});
    if (!place)
      return res.jsonp({err: "Can't find the place!"});
    var name = place.name;
    Place.remove({_id: req.params.id}, function(err, removed){
      if (err)
        return res.jsonp({err: err});
      Link.remove({$or : [{source: name} , {target: name}]}, function(err, removeLink) {
        res.jsonp({
          err: err,
          removed: removed,
          removeLink: removeLink
        });
      })
    });
  });
});

router.get('/link/delete/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: "No id is provided!"});
  }
  Link.remove({_id: req.params.id}, function(err, removed){
    if (err)
      return res.jsonp({err: err});
    res.jsonp(removed);
  });
});

router.post('/place/reset/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: 'No place id provided!'});
  }
  if (!req.body.value) {
    return res.jsonp({err: "The place's name is not provided!"});
  }
  if (!req.body.introduce) {
    return res.jsonp({err: "The place's introduce is not provided!"});
  }
  if (!req.body.x) {
    return res.jsonp({err: "The place's posx is not provided!"});
  }
  if (!req.body.y) {
    return res.jsonp({err: "The place's posy is not provided!"});
  }
  var value = req.body.value, placeUpdate;
  Place.find({}, function(err, places) {
    for (var i = 0; i < places.length; i++) {
      if (places[i].value == value && places[i]._id != req.params.id) {
        return res.jsonp({err: "The place had exist!"});
      }
      if (places[i]._id == req.params.id) {
        placeUpdate = places[i];
      }
    }
    placeUpdate.value = req.body.value;
    placeUpdate.introduce = req.body.introduce;
    placeUpdate.x = req.body.x;
    placeUpdate.y = req.body.y;
    placeUpdate.save(function(err, msg) {
      if (err) {
        return res.jsonp({err: err});
      }
      res.jsonp({err: undefined, msg: msg});
    });
  });
});

router.get('/place/data/:type', function (req, res, next) {
  var conditions = {};
  if (req.params.type) {
    if (!(req.params.type == "all"))
      conditions.type = req.params.type;
  }
  Place.find(conditions, function (err, places) {
    if (err)
      return res.jsonp({
        err: err
      });
    res.jsonp(places);
  });
});

router.get('/link/data/:type', function (req, res, next) {
  var conditions = {};
  if (req.params.type) {
    if (!(req.params.type == "all"))
      conditions.type = req.params.type;
  }
  Link.find(conditions, function (err, links) {
    if (err)
      return res.jsonp({
        err: err
      });
    res.jsonp(links);
  });
});

router.post('/link/reset/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: 'No link id provided!'});
  }
  if (!req.body.source) {
    return res.jsonp({err: "The link's source is not provided!"});
  }
  if (!req.body.target) {
    return res.jsonp({err: "The link's source is not provided!"});
  }
  if (!req.body.value) {
    return res.jsonp({err: "The link's value is not provided!"});
  }
  if (!req.body.type) {
    return res.jsonp({err: "The link's type is not provided!"});
  }
  Link.find({}, function(err, links) {
    if (err) {
      return res.jsonp({err: err});
    }
    var source = req.body.source, target = req.body.target, id = req.params.id, type = req.body.type, linkUpdate;
    for (var i = 0; i < links.length; i++) {
      if (links[i].source == source && links[i].target == target && links[i].type == type && links[i]._id != req.params.id)
        return res.jsonp({err: "The link is exist!"});
      if (links[i].source == target && links[i].target == source && links[i].type == type && links[i]._id != req.params.id)
        return res.jsonp({err: "The link is exist!"});
      if (links[i]._id == id)
        linkUpdate = links[i];
    }
    linkUpdate.source = source;
    linkUpdate.target = target;
    linkUpdate.value = req.body.value;
    linkUpdate.type = type;
    linkUpdate.save(function(err, msg) {
      if (err) {
        return res.jsonp({err: err});
      }
      res.jsonp({err: undefined, msg: msg});
    });
  });
});

router.post('/post/add', function(req, res, next) {
  if (!req.body.path) {
    return res.jsonp({err: "The path is not provided!"});
  }
  if (!req.body.email) {
    return res.jsonp({err: "The author's email is not provided!"});
  }
  if (!req.body.title) {
    return res.jsonp({err: "The post's title is not provided!"});
  }
  if (!req.body.content) {
    return res.jsonp({err: "The post's content is not provided!"});
  }
  var title = req.body.title.trim();
  var content = req.body.content;
  var post = new Post({
    author: req.body.email,
    path: req.body.path,
    title: title,
    content: content,
    meta: { favourites: 0 },
    comments: []
  });

  post.save(function(err, msg) {
    if (err) {
      res.jsonp({err: err});
    } else {
      res.jsonp({err: undefined, msg: msg});
    }
  });
});

router.get('/post/all', function(req, res, next) {
  Post.find({}, function(err, posts) {
    if (err)
      res.jsonp({err: err});
    else
      res.jsonp({posts: posts});
  });
});

router.get('/post/favourite/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: "No id is provided!"});
  }
  var conditions = {};
  try {
    conditions._id = mongoose.Types.ObjectId(req.params.id);
  } catch (err) {
    conditions.title = req.params.id;
  }
  Post.findOne(conditions, function(err, post) {
    if (err)
      return res.jsonp({err: err});
    post.meta.favourites = post.meta.favourites? post.meta.favourites+1 : 1;
    post.markModified('meta');
    post.save(function(err, post) {
      if (err)
        return res.jsonp({err: err});
      res.jsonp(post);
    })
  });
});

router.post('/post/comment/:id', function(req, res, next) {
  if (!req.params.id) {
    return res.jsonp({err: "No id is provided!"});
  }
  if (!req.body.email) {
    return res.jsonp({err: "No email is provided!"});
  }
  if (!req.body.content) {
    return res.jsonp({err: "No content is provided!"});
  }
  var conditions = {};
  try {
    conditions._id = mongoose.Types.ObjectId(req.params.id);
  } catch (err) {
    conditions.title = req.params.id;
  }
  Post.findOne(conditions, function(err, post) {
    if (err)
      return res.jsonp({err: err});
    var newComment = {
      email: req.body.email,
      content: req.body.content
    };
    post.comments.unshift(newComment);
    post.markModified('comments');
    post.save(function(err, post) {
      res.jsonp({
        post: post,
        newComment: newComment
      });
    });
  });
});
