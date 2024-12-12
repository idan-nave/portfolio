import { getCurrentDateTime } from "../getCurrentDateTime.js";

export const insertCustomers = async (connection) => {
  const insertCustomers = await connection.prepare(`
    INSERT INTO customers (name, email, password, createdAt) VALUES (?, ?, ?, ?)
  `);
  await insertCustomers.execute([
    "Dor",
    "Dor@Dor.com",
    "Dor1234",
    getCurrentDateTime(),
  ]);
  await insertCustomers.execute([
    "Moses",
    "Moses@Moses.com",
    "Moses5678",
    getCurrentDateTime(),
  ]);
  await insertCustomers.execute([
    "Sasi",
    "Sasi@Sasi.com",
    "Sasi91011",
    getCurrentDateTime(),
  ]);
  await insertCustomers.close();
};