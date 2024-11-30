// JavaScript to handle basic interactions

// document.addEventListener('DOMContentLoaded', () => {
//     console.log('Static web template loaded!');

//     // logic for once all lcontent is loaded
    
// });

document.addEventListener('DOMContentLoaded', () => {
    console.log('Page loaded and JS is working!');

    // 1. Selecting elements
    const toggleButton = document.getElementById('toggleBtn'); // Select the button with ID 'toggleBtn'
    const descriptionText = document.getElementById('description'); // Select the paragraph with ID 'description'
    const changeTextButton = document.getElementById('changeTextBtn'); // Button to change text content
    const imageElements = document.querySelectorAll('.image-container img'); // Select all images within the class 'image-container'
    const changeImagesButton = document.getElementById('changeImagesBtn'); // Button to change image sources

    // 2. Event listener to toggle background color
    toggleButton.addEventListener('click', () => {
        document.body.style.backgroundColor = document.body.style.backgroundColor === 'lightgray' ? 'white' : 'lightgray'; // Toggle background color
    });

    // 3. Change the text content of the paragraph when the button is clicked
    changeTextButton.addEventListener('click', () => {
        descriptionText.textContent = 'You have successfully changed the text!'; // Change text of the paragraph
    });

    // 4. Change image sources dynamically
    changeImagesButton.addEventListener('click', () => {
        imageElements.forEach(img => {
            img.src = 'media/placeholder.jpg'; // Change all image sources to a new image
        });
    });

    // 5. Adding a class dynamically (common functionality like adding/removing classes)
    const introSection = document.getElementById('intro');
    introSection.addEventListener('mouseenter', () => {
        introSection.classList.add('highlight'); // Add class on mouse enter
    });
    introSection.addEventListener('mouseleave', () => {
        introSection.classList.remove('highlight'); // Remove class on mouse leave
    });

});
