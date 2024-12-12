export const insertGenres = async (connection) => {
  const insertGenres = await connection.prepare(`
    INSERT INTO genres (genreName) VALUES (?)
  `);

  const genres = ["Fantasy", "Adventure", "Comedy", "Romance"];

  for (const genre of genres) {
    await insertGenres.execute([genre]);
  }

  await insertGenres.close();
};