CREATE SCHEMA IF NOT EXISTS  relationships;
USE relationships;

CREATE TABLE IF NOT EXISTS users (
    id INT PRIMARY KEY,
    name VARCHAR(50),
    age INT
);
    
    CREATE TABLE IF NOT EXISTS adresses (
	id INT PRIMARY KEY,
    street_name VARCHAR(50),
    number int,
    user_id int,
    FOREIGN KEY (user_id)
	REFERENCES users (id) 
    );
    
	CREATE TABLE IF NOT EXISTS credit_card (
	id INT PRIMARY KEY,
    card_number CHAR(16),
    cvs CHAR(3),
    exp_month int,
    exp_year int,
    user_id int UNIQUE,
    FOREIGN KEY (user_id)
	REFERENCES users (id) 
    );
    
    
    CREATE TABLE IF NOT EXISTS orders (
	order_number INT PRIMARY KEY,
    final_price int
    );
    
    CREATE TABLE IF NOT EXISTS user_orders (
    user_id int,
    order_id int,
    FOREIGN KEY (user_id)
    REFERENCES users (id),
    FOREIGN KEY (order_id)
    REFERENCES orders (order_number)
    );