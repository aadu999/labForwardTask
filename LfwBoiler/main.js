const labBoiler = require('./build/Release/labfw_boiler');

exports.boiler = {
  async: labBoiler.performAsync
};