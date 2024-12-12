export async function dropTables(connection, tableQueries) {
  try {
    for (const query of tableQueries) {
      await connection.query(query);
    }
    console.log("Existing tables dropped successfully.");
  } catch (error) {
    console.error("Error dropping tables:", error.message);
    throw error; 
  }
}