const mysql = require('mysql2');

const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: 'HAacHF)(#QR9adMnEolf8#TR105',
  database: 'pap_db'
});

module.exports = connection;