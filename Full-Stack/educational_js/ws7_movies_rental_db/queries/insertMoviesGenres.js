export const insertMoviesGenres = async (connection) => {
  const insertMoviesGenres = await connection.prepare(`
    INSERT INTO movies_genres (movie_id, genre_id) VALUES (?, ?)
  `);

  await insertMoviesGenres.execute([1, 1]);
  await insertMoviesGenres.execute([1, 2]);
  await insertMoviesGenres.execute([2, 3]);
  await insertMoviesGenres.execute([2, 4]);

  await insertMoviesGenres.close();
};
