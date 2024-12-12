const sql = require('mysql2');

const dbConn = sql.createConnection(
    {
        host: 'localhost',
        user: 'idan',
        password: 'password',
        database: "MovieRentalDB",
    }
)
const tableQuery =  `   
    CREATE TABLE IF NOT EXISTS customers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password CHAR(10) NOT NULL,
    createdAt DATETIME
    );

    CREATE TABLE IF NOT EXISTS movies (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    description VARCHAR(8000),
    releaseYear INT NOT NULL,
    score FLOAT DEFAULT 0.0
    );

    CREATE TABLE IF NOT EXISTS genres (
    id INT AUTO_INCREMENT PRIMARY KEY,
    genreName VARCHAR(255) NOT NULL
    );

    CREATE TABLE IF NOT EXISTS movies_genres (
    movie_id INT,
    genre_id INT,
    FOREIGN KEY (movie_id) REFERENCES movies (id),
    FOREIGN KEY (genre_id) REFERENCES genres (id),
    PRIMARY KEY (movie_id, genre_id)
    );

    CREATE TABLE IF NOT EXISTS rentals (
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    movie_id INT,
    rentalDate DATETIME NOT NULL,
    isReturned BOOLEAN DEFAULT false,
    returnDate DATETIME,
    FOREIGN KEY (customer_id) REFERENCES customers (id),
    FOREIGN KEY (movie_id) REFERENCES movies (id)
    );`

dbConn.query(tableQuery, resultCallback)

dbConn.end()