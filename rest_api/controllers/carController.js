const car = require('../models/car_model');

exports.getAllCars = function(req, res) {
  car.getAll(function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};

exports.getOneCar = function(req, res) {
  car.getById(req.params.id, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult[0]); 
    }
  });
};

exports.addCar = function(req, res) {
  car.add(req.body, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};

exports.deleteCar = function(req, res) {
  car.delete(req.params.id, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};

exports.updateCar = function(req, res) {
  car.update(req.params.id, req.body, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};