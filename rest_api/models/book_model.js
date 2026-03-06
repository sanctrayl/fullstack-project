const db = require('../database');

const book = {
  getAll: function(callback) {
    return db.query('SELECT * FROM book', callback);
  },
  getById: function(id, callback) {
    return db.query('SELECT * FROM book WHERE id_book=?', [id], callback);
  },
  add: function(bookData, callback) {
    return db.query('INSERT INTO book (name, author) VALUES (?, ?)', 
      [bookData.name, bookData.author], callback);
  },
  delete: function(id, callback) {
    return db.query('DELETE FROM book WHERE id_book=?', [id], callback);
  },
  update: function(id, bookData, callback) {
    return db.query('UPDATE book SET name=?, author=? WHERE id_book=?', 
      [bookData.name, bookData.author, id], callback);
  }
};

module.exports = book;