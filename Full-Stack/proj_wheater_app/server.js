// Hiding your API key
// Use Environment Variables (Server-Side Solution)

// store the API key in environment variables and make API requests through your server.
//     Create a server using Node.js, Python, or any backend language.
//     Store your API key in an environment variable (.env file).
//     Create an endpoint on the server to fetch weather data.
//     Call your server endpoint from the frontend instead of directly calling the OpenWeatherMap API.

// Example with Node.js:
//     Install dependencies:
//     npm install express dotenv axios

require('dotenv').config(); // Load environment variables from .env
const express = require('express');
const axios = require('axios'); // For making HTTP requests
const app = express();

const PORT = 3000; // Port the server will listen on
const API_KEY = process.env.WEATHER_API_KEY; // Access the API key from .env

// Define a route to get weather data
app.get('/weather', async (req, res) => {
  const city = req.query.city; // Get the city parameter from the query string
  if (!city) {
    return res.status(400).send('City is required');
  }

  try {
    // Fetch data from OpenWeatherMap API
    const response = await axios.get(`https://api.openweathermap.org/data/2.5/weather`, {
      params: {
        q: city,
        appid: API_KEY,
        units: 'metric',
      },
    });

    // Send the weather data back to the frontend
    res.json(response.data);
  } catch (error) {
    console.error('Error fetching weather data:', error.message);
    res.status(500).send('Error fetching weather data');
  }
});

// Start the server
app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
