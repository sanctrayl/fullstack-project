const book = require('../models/book_model');

exports.getAllBooks = function(req, res) {
  book.getAll(function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};

exports.getOneBook = function(req, res) {
  book.getById(req.params.id, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult[0]); 
    }
  });
};

exports.addBook = function(req, res) {
  book.add(req.body, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};

exports.deleteBook = function(req, res) {
  book.delete(req.params.id, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};

exports.updateBook = function(req, res) {
  book.update(req.params.id, req.body, function(err, dbResult) {
    if (err) {
      res.json(err);
    } else {
      res.json(dbResult);
    }
  });
};