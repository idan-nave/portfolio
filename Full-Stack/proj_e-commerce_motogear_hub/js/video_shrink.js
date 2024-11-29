// video_shrink.js

// Detecting the end of the video:
// We use the ended event listener to detect when the video
// finishes playing.This happens after the first iteration 
// of the video.
// Apply the.shrink class: When the video finishes the first
// loop, we add the shrink class to the.video_cont element,
// which triggers the transition to shrink the video’s height
// to 2x the header height.
// Ensuring the video loops: In case the video wasn't looping
// initially, we make sure to set the loop attribute to true
// once the video starts playing.

document.addEventListener('DOMContentLoaded', function () {
    const video = document.querySelector('.hero_video');
    const videoCont = document.querySelector('.video_cont');

    // Detect when the video ends the first loop
    video.addEventListener('ended', function () {
        if (video.currentTime > 0 && !video.loop) {
            // Add a class to shrink the video after the first iteration
            videoCont.classList.add('shrink');
        }
    });

    video.addEventListener('play', function () {
        if (!video.loop) {
            video.loop = true; // Ensure the video is looping
        }
    });
});

// .hero_video {
//     transition: height 2s ease; /* Transition for height change */
// }

// .video_cont.shrink .hero_video {
//     height: calc(8vh * 2); /* Shrink the video to 2x the height of the header after the first iteration */
// }