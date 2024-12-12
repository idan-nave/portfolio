const sql = require('mysql2');

const conn = sql.createConnection(
    {
        host: 'localhost',
        user: 'idan',
        password: 'password',
        db: 'jsDB',
    }
)
const schemaSql = "CREATE SCHEMA IF NOT EXISTS MovieRentalDB";
conn.query(schemaSql);

dbConn.end()