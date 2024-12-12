const sql = require('mysql2');

const dbConn = sql.createConnection(
    {
        host: 'localhost',
        user: 'idan',
        password: 'password',
        database: "MovieRentalDB",
    }
)
// dbConn.ping((err) => {
//     if (err) {
//         console.error(err);
//     } else {
//         console.log("PONG")
//     }
// });

function getCurrentTime() {
    const now = new Date();

    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0');
    const day = String(now.getDate()).padStart(2, '0');

    return ${ year } -${ month } -${ day };
}

const errCallback = (err) => {
    if (err) {
        console.error(err);
    }
}

const resultCallback = (err, result) => {
    if (err) {
        errCallback(err)
    } else {
        console.log(result)
    }
}

dbConn.query("USE MovieRentalDB;", errCallback);

dbConn.prepare(`
    INSERT INTO customers
    (name, email, password, createdAt) 
    VALUES (?, ? , ? , ?);`, (err, statement) => {
    if (err) { console.log(err) }
    else {
        statement.execute(["Dor", "ddd@gg", "123456", getCurrentTime()], resultCallback)
        statement.execute(["Moshe", "moddsh@gg", "123456", getCurrentTime()], resultCallback)
        statement.execute(["sasi", "sadds@gg", "123456", getCurrentTime()], resultCallback)
    }
}
)

dbConn.prepare(`
    INSERT INTO movies
    (title, description, releaseYear, score) 
    VALUES (?, ? , ? , ?);`, (err, statement) => {
    if (err) { console.log(err) }
    else {
        statement.execute(["hobbit", "The best movie ever! 1", 2007, 9.9], resultCallback)
        statement.execute(["american pie", "ori requested movie", 2023, 3.2], resultCallback)
        statement.execute(["all the single ladies", "there was a single lady in NY", 2030], resultCallback)
    }
}
)

dbConn.end()