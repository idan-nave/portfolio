
//################### promises ###################

// const username = 'nitay'

// const login = new Promise((resolve, reject) => {
//     if (username === 'nitay') {
//         resolve('hello nitay!')
//     }
//     else {
//         reject('Incorrect username')
//     }
// })

// const getPhoto = new Promise((resolve, reject) => {
//     // resolve('picture')
//     reject('couldnt get photo')
// })

// login
//     .then((data) => {
//         console.log(data);
//         return getPhoto
//     })
//     .then((photoData) => console.log(photoData))
//     .catch((err) => {
//         console.log(err)
//     })
//     .then(() => { })
//     .catch(() => { })


//################### fetch built in promise ###################


// fetch('https://jsonplaceholder.typicode.com/users')
//     .then(data⇒ data.json())
//     .then(jsonData => {
//         jsonData.forEach((value) {
//             console.log(value.name);
//         })
//             .catch(err => {
//                 console.log(err);
//             })
//     };


//################### async, await ###################

// async function pullPlain() {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/users');
//         console.log(data);
//     }
//     catch (err) {
//         console.log(err);
//     }
// }

// async function pullNames() {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/users');
//         const jsonData = await data.json();
//         console.log(typeof jsonData);
//         jsonData.forEach(value => {
//             console.log(value.name);
//         })
//     }
//     catch (err) {
//         console.log(err);
//     }
// }

// pullPlain();


//################### exercises ###################

//################### #1 ###################

// Create a function that receives a parameter of an id and
// fetches from https://jsonplaceholder.typicode.com/posts
// and logs all posts by that userId to the console

// jsonData.filter: Iterates over the array of post objects.
// post: Represents each object in the jsonData array during iteration.
// Filter Condition: post.userId === postid: Only includes posts where the userId matches the postid parameter passed to the fetchPosts function.

// async function fetchPosts(postid) {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/posts');
//         const jsonData = await data.json();
//         const filteredData = jsonData.filter((post) => {
//             return post.userId === postid })
//         console.log(filteredData);

//     }
//     catch (err) {
//         console.log(err);
//     }
// }
// fetchPosts(1);

//################### #2 ###################

// Create a function that returns all comments from
// https://jsonplaceholder.typicode.com/comments
// whose email address ends with '.net'

// async function fetchCommsWithEmails() {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/comments');
//         const jsonData = await data.json();
//         const filteredData = jsonData.filter((value) => {
//             return value.email.endsWith('.net');
//         });
//         console.log(filteredData);
//     } catch (err) {
//         console.log(err);
//     }
// }
// fetchCommsWithEmails();

    
//################### #3 ###################

// Create a function that fetches images from
// https://jsonplaceholder.typicode.com/photos/1
// and displays an image tag with an src value from the api

// async function fetchImages() {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/photos/1');
//         const jsonData = await data.json();
//         const srcImage = jsonData.url;;
//         console.log(srcImage);

//         //create new element with the value from input
//         const newImg = document.createElement('img');
//         //get container underwhich img eill be appeded
//         const cont = document.getElementById('main_cont');
//         //create a new img with the fetched src property
//         newImg.src = srcImage;
//         cont.appendChild(newImg);

//     } catch (err) {
//         console.log(err);
//     }
// }
// fetchImages();
