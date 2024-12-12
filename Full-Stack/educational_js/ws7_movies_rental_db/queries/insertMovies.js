export const insertMovies = async (connection) => {
  const insertMovies = await connection.prepare(`
      INSERT INTO movies (title, description, releaseYear, score) VALUES (?, ?, ?, ?)
    `);
    await insertMovies.execute([
      "The Hobbit",
      "A fantasy adventure following Bilbo Baggins on an epic quest",
      2012,
      7.8,
    ]);
    await insertMovies.execute([
      "American Pie",
      "A coming-of-age comedy about high school friends navigating life and love",
      1999,
      7.0,
    ]);
  await insertMovies.close();
};
