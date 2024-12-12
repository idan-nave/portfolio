const sql = require('mysql2');

// const schemaSql = "CREATE SCHEMA IF NOT EXISTS jsDB";
// conn.query(schemaSql);

// const db = sql.createConnection(
//     {
//         host: 'localhost',
//         user: 'idan',
//         password: 'password',
//         db: 'jsDB',
//     }
// )

const dbConn = sql.createConnection(
    {
        host: 'localhost',
        user: 'idan',
        password: 'password',
        db: 'jsDB',
    }, (err, result) => {
        if (err) {
            console.errors(err);
        } else {
            console.log("Connection Established");
            console.log(result);

        }
    });

// const schemaSql = "CREATE SCHEMA IF NOT EXISTS jsDB";
dbConn.query("USE jsDB", (err, result) => {
    if (err) {
        console.errors(err);
    } else {
        console.log("using jsDB: ");
        console.log(result);

    }
});

dbConn.ping((err, result) => {
    if (err) {
        console.errors(err);
    } else {
        console.log("PONG recieved");
        console.log(result);

    }
});
dbConn.end();