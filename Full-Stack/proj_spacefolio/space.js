// space.js

function syncVideoWithCockpit() {
    const cockpitImage = document.getElementById('cockpit-image');
    const videoElement = document.querySelector('.background-video');
    const cockpitContainer = document.querySelector(".cockpit");

    // Get the bounding rectangle of the cockpit image
    const cockpitRect = cockpitImage.getBoundingClientRect();

    // Calculate the required video height based on the cockpit's height
    const cockpitHeight = cockpitRect.height;

    // Set the CSS custom property for video clipping based on the cockpit height
    videoElement.style.setProperty('--video-height', `${cockpitHeight}px`);

    // Update the video element's position to keep it aligned with the cockpit
    //also decrese by 10px to accommodate for the subtle movement effect
    videoElement.style.height = `${cockpitHeight - 10}px`;
    videoElement.style.top = `${cockpitRect.top}px`;

    // Optionally, apply the object-fit to ensure the video covers the viewport
    videoElement.style.objectFit = 'cover';
    
    // Apply subtle movement to cockpit container
    cockpitContainer.style.animation = "subtle-move 4s ease-in-out infinite";
}

// Call the function initially and on window resize
window.addEventListener('load', syncVideoWithCockpit);
window.addEventListener('resize', syncVideoWithCockpit);
