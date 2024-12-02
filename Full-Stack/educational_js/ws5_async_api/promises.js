//######################## Promises ########################


//######################## Example 1: Handling Promises ########################

// Demonstrates creating and using Promises for login and fetching a photo.
const username = 'nitay';

const login = new Promise((resolve, reject) => {
    if (username === 'nitay') {
        resolve('Hello, Nitay!'); // Resolved if the username matches
    } else {
        reject('Incorrect username'); // Rejected if the username does not match
    }
});

const getPhoto = new Promise((resolve, reject) => {
    // Uncomment resolve or reject to test each behavior
    // resolve('Photo fetched successfully!');
    reject('Couldn’t fetch the photo.');
});

// Chain Promises with .then() and handle errors with .catch()
login
    .then((message) => {
        console.log(message); // Output: Hello, Nitay!
        return getPhoto; // Returns the next Promise in the chain
    })
    .then((photoMessage) => {
        console.log(photoMessage); // Logs photo message if resolved
    })
    .catch((error) => {
        console.log('Error:', error); // Catches errors from login or getPhoto
    });

//######################## Example 2: Fetch API with Promises ########################

// Demonstrates fetching user data from an API using .then() chaining.
fetch('https://jsonplaceholder.typicode.com/users')
    .then((response) => response.json()) // Converts response to JSON
    .then((users) => {
        users.forEach((user) => {
            console.log(user.name); // Logs each user's name
        });
    })
    .catch((error) => {
        console.log('Fetch Error:', error); // Handles fetch errors
    });

//######################## Example 3: Async Array Processing ########################

// Goal: Create a function that processes values in an array based on certain conditions.
// 1. For each number in the array, determine if it is even or odd.
// 2. Create a new array with strings describing the original numbers (e.g., "2 is even").
// 3. Implement an asynchronous function to simulate processing time.


    async function describeNumbersAsync(numbers) {
        const result = [];
        for (const num of numbers) {
            await delay(500); // Simulate processing time (500ms delay)
            if (num % 2 === 0) {
                result.push(`${num} is even`);
            } else {
                result.push(`${num} is odd`);
            }
        }
        return result;
    }

//######################## Example 4:  Array Processor Promise, Resolve ########################

// The function will iterate through the array and apply the following rules: If the number is even, add it to a new array; if it is odd, skip it .
// Once you process the entire array, return the new array containing only the even numbers .
// Additionally, implement an asynchronous function that simulates a delay using setTimeout,
// allowing the processed result to be displayed after a specified time. . 


async function processArray(array) {
    const evenNumbers = [];
  
    // Wrap the setTimeout logic in a Promise
    await new Promise((resolve) => {
      setTimeout(() => {
        for (let i = 0; i < array.length; i++) {
          if (array[i] % 2 === 0) evenNumbers.push(array[i]);
        }
        resolve(); // Resolve the Promise when processing is done
      }, 1000);
    });
  
    return evenNumbers;
  }
  
  // Example usage
  const numbers = [1, 2, 3, 4, 5, 6];
  processArray(numbers).then((result) => console.log(result)); // Output after 1 second: [2, 4, 6]
  
