// Function to fetch countries and populate the dropdown
async function fetchCountries() {
    const dropdown = document.getElementById('images-titles-dropdown');
    
    try {
        // Show loading state
        dropdown.innerHTML = '<option value="">Loading...</option>';

        // Fetch data from ImagePlaceholder API
        const response = await fetch('https://jsonplaceholder.typicode.com/photos');
        
        // Check if the response is successful (status code 200)
        if (!response.ok) {
            throw new Error('Failed to fetch data');
        }

        // Parse the response data as JSON
        const data = await response.json();

        // Clear the dropdown (remove "Loading..." option)
        dropdown.innerHTML = '';

        // Populate the dropdown with image titles
        // Use only the first 10 images for brevity
        data.slice(0, 10).forEach(image => {
            const option = document.createElement('option');
            option.value = image.url; // Image URL as value
            option.textContent = image.title; // Image title as text
            dropdown.appendChild(option);
        });

    } catch (error) {
        // Handle errors and show a user-friendly message
        console.error('Error fetching images:', error);
        dropdown.innerHTML = '<option value="">Failed to load images</option>';
    }
}

// Call the function to fetch countries when the page loads
document.addEventListener('DOMContentLoaded', () => {
    fetchCountries();
});
