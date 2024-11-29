/* cockpit.js */

import { controlHome, shopOnline, shieldToggle, taskScheduler, timeHalt, timeTravel, destroyEarth, destroySelf, contactSupport, pilotCreds, networkBringup, srcCode } from './interact.js';

document.addEventListener("DOMContentLoaded", () => {
    const cockpitImage = document.getElementById("cockpit-image");
    const cockpitContainer = document.querySelector(".cockpit");

    // Original image map coordinates, types, colors, rotation, and skew
    const buttonCoordinates = [
        // 4 top left circles
        { id: "control_home", x: 64, y: 10, type: "circle", color: "rgba(0, 255, 0, 0.5)", rotation: 0, skew: "10deg", tooltip: "Control Home" },
        { id: "shop_online", x: 22, y: 22, type: "circle", color: "rgba(255, 0, 0, 0.5)", rotation: 0, skew: "10deg", tooltip: "Shop Online" },
        { id: "shield_toggle", x: 21, y: 48, type: "circle", color: "rgba(0, 0, 255, 0.5)", rotation: 0, skew: "10deg", tooltip: "Toggle Shields" },
        { id: "task_scheduler", x: 55, y: 40, type: "circle", color: "rgba(255, 255, 0, 0.5)", rotation: 0, skew: "10deg", tooltip: "Task Scheduler" },
        // 2 top left recs
        { id: "time_halt", x: 130, y: 32, type: "rect", color: "rgba(255, 0, 255, 0.5)", rotation: -10, skew: "30deg", tooltip: "Halt Space-Time [USE WITH CAUTION]" },
        { id: "time_travel", x: 189, y: 20, type: "rect", color: "rgba(0, 255, 255, 0.5)", rotation: -10, skew: "30deg", tooltip: "Time Travel" },
        // 3 top right Tris
        { id: "destroy_earth", x: 338, y: 8, type: "circle", color: "rgba(0, 255, 0, 0.5)", rotation: 0, skew: "10deg", tooltip: "Destroy Earth" },
        { id: "destroy_self", x: 400, y: 6, type: "circle", color: "rgba(255, 0, 0, 0.5)", rotation: 0, skew: "10deg", tooltip: "Destroy Self" },
        { id: "contact_support", x: 450, y: 4, type: "circle", color: "rgba(0, 0, 255, 0.5)", rotation: 0, skew: "10deg", tooltip: "Contact Space-Time Support" },
        // 1 top right square
        { id: "X", x: 510, y: 0, type: "square", color: "rgba(255, 165, 0, 0.5)", rotation: 0, skew: "-15deg", tooltip: "X" },
        // 1 left circle
        { id: "pilot_credentials", x: 107, y: 273, type: "circle", color: "rgba(255, 165, 0, 0.5)", rotation: 0, skew: "0deg", tooltip: "Pilot Credentials [SECRET]" },
        // 1 left square
        { id: "source_code", x: 114, y: 245, type: "square", color: "rgba(255, 255, 255, 0.5)", rotation: 10, skew: "-20deg", tooltip: "Space-Time Source Code" },
        // 1 right circle
        { id: "network_bringup", x: 420, y: 326, type: "circle", color: "rgba(128, 0, 128, 0.5)", rotation: 0, skew: "0deg", tooltip: "Network Bringup" },
    ];

    const originalWidth = 626;
    const originalHeight = 351;

    // Create the spaceship monitor (video box)
    const monitorBox = document.createElement("div");
    monitorBox.id = "spaceship-monitor";
    cockpitContainer.appendChild(monitorBox);

    // Create the video element inside the monitor box
    const video = document.createElement("video");
    video.src = "media/videos/monitor.webm";
    video.loop = true;
    video.autoplay = true;
    video.muted = true;
    monitorBox.appendChild(video);

    // Create the dynamic message overlay
    const messageOverlay = document.createElement("div");
    messageOverlay.id = "monitor-message";
    messageOverlay.innerText = "Full-Stack & Embedded Developer";
    monitorBox.appendChild(messageOverlay);

    // Create the static message overlay
    const staticMessage = document.createElement("div");
    staticMessage.id = "static-message";
    staticMessage.innerText = "Pilot: IDAN NAVE"; // Add your static message here
    monitorBox.appendChild(staticMessage);


    // Function to adjust button positions dynamically based on image scaling
    const adjustButtonPositions = () => {
        const cockpitRect = cockpitImage.getBoundingClientRect();
        const scaleX = cockpitRect.width / originalWidth;
        const scaleY = cockpitRect.height / originalHeight;

        // Remove existing buttons
        document.querySelectorAll(".button").forEach((btn) => btn.remove());

        // Add buttons dynamically
        buttonCoordinates.forEach((coord) => {
            const button = document.createElement("div");
            button.className = `button ${coord.type}`;
            button.style.left = `${cockpitRect.left + coord.x * scaleX}px`;
            button.style.top = `${cockpitRect.top + coord.y * scaleY}px`;
            button.style.backgroundColor = coord.color;  // Use the custom color for each button
            button.style.transform += `rotate(${coord.rotation}deg) skew(${coord.skew})`;
            button.setAttribute("data-tooltip", coord.tooltip);  // Set the tooltip data

            // Add hover effect to update the message in the monitor
            button.addEventListener("mouseenter", () => {
                messageOverlay.innerText = coord.tooltip; // Update the monitor message on hover
            });
            button.addEventListener("mouseleave", () => {
                messageOverlay.innerText = "Full-Stack & Embedded Developer"; // Reset the message
            });

            cockpitContainer.appendChild(button);
        });
    };

    const assignFunctionality = () => {
        buttonCoordinates.forEach(({ id }) => {
            const button = document.getElementById(id);

            if (!button) return;

            switch (id) {
                case "control_home":
                    button.addEventListener("click", controlHome);
                    break;
                case "shop_online":
                    button.addEventListener("click", shopOnline);
                    break;
                case "shield_toggle":
                    button.addEventListener("click", shieldToggle);
                    break;
                case "task_scheduler":
                    button.addEventListener("click", taskScheduler);
                    break;
                case "time_halt":
                    button.addEventListener("click", timeHalt);
                    break;
                case "time_travel":
                    button.addEventListener("click", timeTravel);
                    break;
                case "destroy_earth":
                    button.addEventListener("click", destroyEarth);
                    break;
                case "destroy_self":
                    button.addEventListener("click", destroySelf);
                    break;
                case "contact_support":
                    button.addEventListener("click", contactSupport);
                    break;
                case "pilot_credentials":
                    button.addEventListener("click", pilotCreds);
                    break;
                case "network_bringup":
                    button.addEventListener("click", networkBringup);
                    break;
                case "source_code":
                    button.addEventListener("click", srcCode);
                    break;
                // Add more cases for additional buttons...
            }
        });
    };

    // Adjust positions on load and resize
    adjustButtonPositions();
    assignFunctionality();

});
