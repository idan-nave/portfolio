// Get all radio buttons and images
const radios = document.querySelectorAll('.radio_input');
const images = document.querySelectorAll('.product_image');

// Add hover event listeners
radios.forEach(radio => {
    radio.addEventListener('mouseenter', () => {
        // Hide all images
        images.forEach(img => img.style.opacity = '0');

        // Show the corresponding image
        const targetImage = document.querySelector(`#img-${radio.id}`);
        if (targetImage) {
            targetImage.style.opacity = '1';
        }
    });
});

// Optional: Reset images when leaving the radios
document.querySelector('.radio_global').addEventListener('mouseleave', () => {
    images.forEach(img => img.style.opacity = '0');
});