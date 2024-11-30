/* interact.js */

export const contentOverlay = document.getElementById('content-overlay');

export const updateDynamicContent = (overlayContent) => {
   // Inject the overlay content
   contentOverlay.innerHTML = overlayContent || '';
};

// Define the functionalities for each button
export const controlHome = () => {
   //
};

export const shopOnline = () => {
   updateDynamicContent({
            overlayContent: `<iframe src="https://google.com" style="width: 100%; height: 80vh; border: none;"></iframe>`
         });
};

export const shieldToggle = () => {
   const cockpitContainer = document.querySelector(".cockpit");

   // Check if the shield effect already exists
   let shieldEffect = document.querySelector(".shield-effect");
   if (!shieldEffect) {
      // Create a new shield effect
      shieldEffect = document.createElement("div");
      shieldEffect.classList.add("shield-effect");

      // Add the shield effect to the cockpit container
      cockpitContainer.appendChild(shieldEffect);

      // Set a timeout to remove the shield effect after some time
      setTimeout(() => {
         shieldEffect.remove();
      }, 5000); // Remove after 5 seconds
   }
};


export const taskScheduler = () => {
   //
};

export const timeHalt = () => {
   // Select the Earth video element using its class
   const earthVideo = document.querySelector(".background-video");

   if (earthVideo) {
      if (earthVideo.paused) {
         earthVideo.play(); // Play the video if it's paused
         console.log("Earth video resumed.");
      } else {
         earthVideo.pause(); // Pause the video if it's playing
         console.log("Earth video paused.");
      }
   } else {
      console.error("Earth video element not found.");
   }
};


export const timeTravel = () => {
   //
};

export const destroyEarth = () => {
   // Select the Earth video element using its class
   const video = document.querySelector(".background-video");
   video.src = "media/videos/destroy_earth.mp4";
   video.loop = false;
   video.autoplay = true;
   video.muted = true;
};

export const destroySelf = () => {
   // Attempt to close the current tab
   if (window.close) {
      window.close();
   } else {
      console.warn("Unable to close the tab. This might not work for tabs opened manually.");
   }
};


export const contactSupport = () => {
   //
};

export const pilotCreds = () => {
   //
};

export const networkBringup = () => {
   //
};
export const srcCode = () => {
   //
};
// Add more functions as needed...




// Example button handlers
// export const showPDF = () => {
//    updateDynamicContent({
//       overlayContent: `<iframe src="media/pdfs/example.pdf" style="width: 100%; height: 80vh; border: none;"></iframe>`
//    });
// };

// export const showWebsite = () => {
//    updateDynamicContent({
//       overlayContent: `<iframe src="https://example.com" style="width: 100%; height: 80vh; border: none;"></iframe>`
//    });
// };
