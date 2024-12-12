import { connection } from "./connection.js";
import { createTableQueries } from "./constants/createTableQueries.js";
import { dropTableQueries } from "./constants/dropTableQueries.js";
import { startDB } from "./queries/startDB.js";
import { dropTables } from "./queries/dropTables.js";
import { createTables } from "./queries/createTables.js";
import { insertData } from "./queries/insertData.js";

async function setupDatabase() {
  try {
    await startDB(connection);

    await dropTables(connection, dropTableQueries);

    await createTables(connection, createTableQueries);

    await insertData(connection);

    console.log("Database setup completed.");
  } catch (error) {
    console.error("Error setting up database:", error.message);
  } finally {
    await connection.end();
  }
}

await setupDatabase();