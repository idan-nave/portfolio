import { insertCustomers } from "./insertCustomers.js";
import { insertMovies } from "./insertMovies.js";
import { insertGenres } from "./insertGenres.js";
import { insertRentals } from "./insertRentals.js";
import { insertMoviesGenres } from "./insertMoviesGenres.js";

export const insertData = async (connection) => {
  try {
    console.log("Starting data insertion...");

    try {
      await insertCustomers(connection);
    } catch (error) {
      console.error("Error inserting customers:", error.message);
      throw error;
    }

    try {
      await insertMovies(connection);
    } catch (error) {
      console.error("Error inserting movies:", error.message);
      throw error;
    }

    try {
      await insertGenres(connection);
    } catch (error) {
      console.error("Error inserting genres:", error.message);
      throw error;
    }

    try {
      await insertRentals(connection);
    } catch (error) {
      console.error("Error inserting rentals:", error.message);
      throw error;
    }

    try {
      await insertMoviesGenres(connection);
    } catch (error) {
      console.error(
        "Error inserting movies-genres relationships:",
        error.message
      );
      throw error;
    }

    console.log("Data insertion completed.");
  } catch (error) {
    console.error("Unexpected error during data insertion:", error.message);
    throw error;
  }
};
