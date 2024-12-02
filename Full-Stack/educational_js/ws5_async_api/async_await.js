//########################   Examples ########################

/// Exercise 1: Fetch Posts by UserId
// Fetches posts from the API and filters them by a given userId.
async function fetchPosts(userId) {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/posts');
        const posts = await response.json();
        const filteredPosts = posts.filter((post) => post.userId === userId);
        console.log(`Posts by user ${userId}:`, filteredPosts);
    } catch (error) {
        console.log('Error fetching posts:', error);
    }
}
fetchPosts(1);

// Exercise 2: Fetch Comments with Emails Ending in '.net'
// Fetches comments and filters those whose email addresses end with '.net'.
async function fetchCommsWithEmails() {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/comments');
        const comments = await response.json();
        const filteredComments = comments.filter((comment) => comment.email.endsWith('.net'));
        console.log('Comments with .net emails:', filteredComments);
    } catch (error) {
        console.log('Error fetching comments:', error);
    }
}
fetchCommsWithEmails();

// Exercise 3: Fetching Data with Async/Await 
// Fetches user names and logs them using async/await.
async function pullNames() {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/users');
        const users = await response.json();
        users.forEach((user) => {
            console.log(user.name); // Logs each user's name
        });
    } catch (error) {
        console.log('Error:', error);
    }
}
// Call the async functions
pullNames();

// Exercise 4: Fetch Posts by UserId
// Fetches posts from an API and filters them by a given userId.
async function fetchPosts(userId) {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/posts');
        const posts = await response.json();
        const filteredPosts = posts.filter((post) => post.userId === userId);
        console.log(`Posts by user ${userId}:`, filteredPosts);
    } catch (error) {
        console.log('Error fetching posts:', error);
    }
}
fetchPosts(1);

// Exercise 5: Fetch and Display an Image
// Fetches an image from the API and displays it on a webpage.
async function fetchImages() {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/photos/1');
        const photo = await response.json();
        console.log('Image URL:', photo.url);

        // Create and append an image element to the DOM
        const newImg = document.createElement('img');
        newImg.src = photo.url; // Set the image source
        document.getElementById('main_cont').appendChild(newImg); // Append to container
    } catch (error) {
        console.log('Error fetching image:', error);
    }
}

// Ensure an HTML element with id 'main_cont' exists
// Example: <div id="main_cont"></div>
fetchImages();
