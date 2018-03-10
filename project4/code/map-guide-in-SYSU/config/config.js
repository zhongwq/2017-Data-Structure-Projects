var path = require('path'),
    rootPath = path.normalize(__dirname + '/..'),
    env = process.env.NODE_ENV || 'development';

var config = {
  development: {
    root: rootPath,
    app: {
      name: 'map-guide-in-sysu'
    },
    port: process.env.PORT || 8000,
    db: 'mongodb://localhost/map-guide-in-sysu'
  },

  test: {
    root: rootPath,
    app: {
      name: 'map-guide-in-sysu'
    },
    port: process.env.PORT || 8000,
    db: 'mongodb://localhost/map-guide-in-sysu-test'
  },

  production: {
    root: rootPath,
    app: {
      name: 'map-guide-in-sysu'
    },
    port: process.env.PORT || 8000,
    db: 'mongodb://localhost/map-guide-in-sysu-production'
  }
};

module.exports = config[env];
