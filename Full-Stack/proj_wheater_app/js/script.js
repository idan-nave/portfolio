const apiKey = 'YOUR_API_KEY'; // Replace with your OpenWeatherMap API key
const weatherForm = document.getElementById('weather-form');
const locationInput = document.getElementById('location');
const weatherInfo = document.getElementById('weather-info');

weatherForm.addEventListener('submit', function(event) {
  event.preventDefault();
  const location = locationInput.value;

  // Fetch weather data
  getWeather(location);
});

function getWeather(location) {
    const url = `http://localhost:3000/weather?city=${location}`; // Call the server endpoint
  
    fetch(url)
      .then(response => response.json())
      .then(data => {
        if (data.cod === 200) {
          displayWeather(data);
        } else {
          alert('City not found!');
        }
      })
      .catch(error => {
        console.error('Error fetching weather data:', error);
        alert('Failed to fetch weather data. Please try again later.');
      });
  }
  

function displayWeather(data) {
  const { main, weather, wind } = data;
  const temp = main.temp;
  const condition = weather[0].description;
  const icon = weather[0].icon;
  
  // Set background image based on weather condition
  document.body.style.backgroundImage = `url('https://openweathermap.org/img/wn/${icon}@2x.png')`;
  document.body.style.backgroundSize = 'cover';
  document.body.style.backgroundPosition = 'center';
  
  const weatherHTML = `
    <div class="weather">
      <h2>${data.name}</h2>
      <p>Temperature: ${temp}°C</p>
      <p>Condition: ${condition}</p>
      <p>Wind Speed: ${wind.speed} m/s</p>
      <img src="https://openweathermap.org/img/wn/${icon}@2x.png" alt="${condition}">
    </div>
  `;

  weatherInfo.innerHTML = weatherHTML;
  weatherInfo.style.display = 'block';
}
