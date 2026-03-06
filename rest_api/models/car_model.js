const db = require('../database');

const car = {
  getAll: function(callback) {
    return db.query('SELECT * FROM car', callback);
  },
  getById: function(id, callback) {
    return db.query('SELECT * FROM car WHERE id=?', [id], callback);
  },
  add: function(carData, callback) {
    return db.query('INSERT INTO car (brand, model) VALUES (?, ?)', 
      [carData.brand, carData.model], callback);
  },
  delete: function(id, callback) {
    return db.query('DELETE FROM car WHERE id=?', [id], callback);
  },
  update: function(id, carData, callback) {
    return db.query('UPDATE car SET brand=?, model=? WHERE id=?', 
      [carData.brand, carData.model, id], callback);
  }
};

module.exports = car;