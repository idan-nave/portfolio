export async function createTables(connection, tableQueries) {
  try {
    console.log("Creating tables...");
    for (const query of tableQueries) {
      await connection.query(query);
    }
    console.log("Tables created successfully.");
  } catch (error) {
    console.error("Error creating tables:", error.message);
    throw error; 
  }
}
