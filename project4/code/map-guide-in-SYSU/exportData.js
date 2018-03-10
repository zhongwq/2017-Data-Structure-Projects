/**
 * Created by zhongwq on 2017/12/25.
 */
/**
 * Created by zhongwq on 2017/12/17.
 */

var config = require('./config/config'),
  glob = require('glob'),
  mongoose = require('mongoose'),
  fs = require('fs');

mongoose.connect(config.db);
console.log(config.db);

var db = mongoose.connection;
db.on('error', function () {
  throw new Error('unable to connect to database at ' + config.db);
});

var models = glob.sync(config.root + '/app/models/*.js');
models.forEach(function (model) {
  require(model);
});

var Place = mongoose.model('Place'),
  Link = mongoose.model('Link');

function exportData() {
  var placeData;
  Place.find({}, function (err, places) {
    placeData = places;
    fs.appendFileSync('outputData.txt', places.length+"\r");
    for (var i = 0; i < places.length; i++) {
      fs.appendFileSync('outputData.txt', places[i].value+"\r");
      fs.appendFileSync('outputData.txt', places[i].introduce+"\r");
    }
  }).then(function() {
    var matrix = new Array();
    for (var i = 0; i < placeData.length; i++)
      matrix[i] = new Array();
    for (var i = 0; i < placeData.length; i++)
      for (var j = 0; j < placeData.length; j++)
        matrix[i][j] = 0;
    Link.find({}, function(err, links) {
      if (err)
        console.log(err);
      //console.log(links);
      for (var i = 0; i < links.length; i++) {
        console.log(links[i].type);
        if (links[i].type == 0) {
          var x = findIndex(links[i].source, placeData);
          var y = findIndex(links[i].target, placeData);
          matrix[x][y] = links[i].value;
          matrix[y][x] = links[i].value;
          console.log("set", matrix[x][y], links[i].value);
        }
      }
      for (var i = 0; i < placeData.length; i++) {
        for (var j = 0; j < placeData.length; j++) {
          fs.appendFileSync('outputData.txt', matrix[i][j] + " ");
        }
        fs.appendFileSync('outputData.txt', "\r");
      }
    })
  }).then(function() {
    var matrix = new Array();
    for (var i = 0; i < placeData.length; i++)
      matrix[i] = new Array();
    for (var i = 0; i < placeData.length; i++)
      for (var j = 0; j < placeData.length; j++)
        matrix[i][j] = 0;
    Link.find({}, function(err, links) {
      if (err)
        console.log(err);
      //console.log(links);
      for (var i = 0; i < links.length; i++) {
        if (links[i].type == 1) {
          var x = findIndex(links[i].source, placeData);
          var y = findIndex(links[i].target, placeData);
          matrix[x][y] = links[i].value;
          matrix[y][x] = links[i].value;
          console.log("set", matrix[x][y], links[i].value);
        }
      }
      for (var i = 0; i < placeData.length; i++) {
        for (var j = 0; j < placeData.length; j++) {
          fs.appendFileSync('outputData.txt', matrix[i][j] + " ");
        }
        fs.appendFileSync('outputData.txt', "\r");
      }
    })
  });
}

function findIndex(name, places) {
  for (var i = 0; i < places.length; i++) {
    if (places[i].name == name) {
      return i;
    }
  }
  return -1;
}

exportData();
