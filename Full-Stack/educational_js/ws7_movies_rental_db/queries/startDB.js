export async function startDB(connection) {
  try {
    console.log("Initializing database...");

    await connection.query("CREATE DATABASE IF NOT EXISTS jsdb;");
    console.log("Database `jsdb` created or already exists.");

    await connection.query("USE jsdb;");
    console.log("Using DB: `jsdb`.");

  } catch (error) {
    console.error("Error initializing the database:", error.message);
    throw error;
  }
}
