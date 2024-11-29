const taskGrid = document.getElementById("task-grid");
const addTaskPlaceholder = document.getElementById("add-task-placeholder");
const clearCompletedBtn = document.getElementById("clear-completed-btn");

const colors = [
    "#e4d0b3", // Soft sand beige
    "#b3c7d6", // Light slate blue
    "#d2b8d2", // Light lavender
    "#c2e0b7", // Pale mint green
    "#f2d0a2", // Soft apricot
    "#c7c0d8", // Muted lavender gray
    "#b2d8d3", // Light teal
    "#e5c7a1", // Light goldenrod
    "#f1d2d6", // Soft rose pink
    "#c9e4c5"  // Pale moss green
];

// Generate a random color
function getRandomColor() {
    return colors[Math.floor(Math.random() * colors.length)];
}

// Add a new task
function addNote(headerText = "New Task", bodyText = "This is a new task description.") {
    const note = document.createElement("div");
    note.className = "note";
    note.style.backgroundColor = getRandomColor();

    // Pin (delete button)
    const pin = document.createElement("img");
    pin.src = "pin.png";
    pin.alt = "Delete";
    pin.className = "pin";

    // Hover effect on pin
    pin.onmouseover = () => {
        pin.classList.add("pin-hover-delete");
        note.classList.add("note-hover-delete");
    };

    pin.onmouseout = () => {
        pin.classList.remove("pin-hover-delete");
        note.classList.remove("note-hover-delete");
    };

    // Delete animation
    pin.onclick = () => {
        pin.classList.add("pin-thrown");
        note.classList.add("note-fade-out");
        setTimeout(() => taskGrid.removeChild(note), 500); // Wait for animations to complete
    };

    // Editable header
    const noteHeader = document.createElement("h3");
    noteHeader.className = "note-header";
    noteHeader.contentEditable = "true";
    noteHeader.textContent = headerText;

    // Editable body
    const noteBody = document.createElement("p");
    noteBody.className = "note-body";
    noteBody.contentEditable = "true";
    noteBody.textContent = bodyText;

    // Complete button (pencil) - Create & Style
    const completeBtn = document.createElement("button");
    completeBtn.className = "complete-btn";
    completeBtn.innerHTML = "✏️"; //pencil icon
    completeBtn.onclick = () => {
        noteHeader.classList.toggle("completed");
        noteBody.classList.toggle("completed");
    };

    // Append elements
    note.appendChild(pin);
    note.appendChild(noteHeader);
    note.appendChild(noteBody);
    note.appendChild(completeBtn);
    taskGrid.insertBefore(note, addTaskPlaceholder); //keep unshifting placeholder
}

// Event for the "Add Task" placeholder
addTaskPlaceholder.addEventListener("click", () => addNote());

// Event to clear completed tasks
clearCompletedBtn.addEventListener("click", () => {
    const allNotes = document.querySelectorAll(".note");
    allNotes.forEach(note => {
        if (note.querySelector(".note-header").classList.contains("completed")) {
            note.classList.add("note-fade-out");  // Add fade-out effect
            setTimeout(() => taskGrid.removeChild(note), 500); // Wait for the fade-out animation
        }
    });
});


// ##### THIS SCRIPT IMPLEMENTS CLOSURE FUNCTIONALITY #######

// A closure in JavaScript is a fundamental concept where a function "remembers" the variables and environment in which it was created, even after the function has finished executing.

// This "remembering" happens because of how JavaScript handles scope and execution contexts. Closures allow inner functions to access variables defined in their outer lexical scope, even if the outer function has already completed.

// IN OUR CASE:
// When 'addNote' creates DOM elements like pin or note and appends them to the page, these elements persist in the DOM tree. The event listeners (e.g., pin.onmouseover) are part of the DOM's internal data structure, not the scope of your JavaScript function.

//Even after the addNote function exits, the pin and note DOM elements exist in the page. The browser knows to run the onmouseover or onclick handlers when those elements are interacted with.

// The event listeners capture a reference to their enclosing environment, implementing closure. This means the pin.onmouseover or pin.onclick functions still have access to variables and context that were defined in addNote, such as 'note'.