import {getCurrentDateTime} from "../getCurrentDateTime.js"
export const insertRentals = async (connection) => {
  const insertRentals = await connection.prepare(`
    INSERT INTO rentals (customer_id, movie_id, rentalDate, isReturned, returnDate) VALUES (?, ?, ?, ?, ?)
  `);
  await insertRentals.execute([
    1,
    1,
    getCurrentDateTime(),
    true,
    getCurrentDateTime(),
  ]);
  await insertRentals.execute([2, 2, getCurrentDateTime(), false, null]);
  await insertRentals.close();
};