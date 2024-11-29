/*
 * File: script.js
 * Description: Adds interactive animation to the spinning image.
 * Author: Your Name
 * Date: YYYY-MM-DD
 * Dependencies: None (or specify any libraries like jQuery, if used)
 */


'use strict'; // Enforce strict mode

// Function to start animation when the image is clicked
function start_animation_spin() {
    const image = document.querySelector('.a_fly_btn');
    
    // Check if the image element exists before applying animation
    if (!image) {
        console.error('Image element not found');
        return;
    }

    // Apply the animation
    image.style.animation = 'spin-and-move 20s linear infinite';
}

// Ensure DOM is fully loaded before attaching event listeners
document.addEventListener('DOMContentLoaded', function() {
    // Attach the click event to the image
    const image = document.querySelector('.a_fly_btn');
    
    if (image) {
        image.addEventListener('click', start_animation_spin);
    } else {
        console.error('Spinning image element not found!');
    }
});
