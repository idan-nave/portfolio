// setTimeout(() => {
//     console.log('delay');
// }, 1 * 1000);
// console.log('hello');
// console.log('world');

// function func() {

// }

// const func = () => {

// }

// () => {}


// let x = 5
// x = () => console.log('function is value');
// x()
// x = 3

// function bigFunc(callBack) {
//     callBack()
// }

// bigFunc(() => {console.log('call back function')})

// [1,2,3].map((num) => num * 2)

// function returnFunc() {
//     console.log('big function only');
//     return () => console.log('returned function');
// }

// const x = returnFunc();
// x()
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
//     // reject('couldnt get photo')
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

// async function func() {
//     try {
//         const message = await login;
//         console.log(message);

//     }
//     catch (err) {
//         console.log(err);
//     }
// }
// console.log(func());

// fetch('https://jsonplaceholder.typicode.com/users')
//     .then(data => data.json())
//     .then(jsonData => {
//         jsonData.forEach((value) => {
//             console.log(value.name)
//         })
//     })
//     .catch(err => {
//         console.log(err);
//     })

// async function pull() {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/users');
//         const jsonData = await data.json();
//         jsonData.forEach(value => {
//             console.log(value.name);
//         })

//         const obj = {
//             userId: 'hello'
//         }
//         const arr = [1, 2, 3, 4]
//         const filteredArr = arr.filter((value) =>  value.userId === userId);
//         filteredArr = [3, 4]
//     }
//     catch (err) {
//         console.log(err);
//     }

// }

// pull()

// Create a function that receives a parameter of an id and
// fetches from https://jsonplaceholder.typicode.com/posts
// and logs all posts by that userId to the console

// async function posts(id) {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/posts');
//         const jsonData = await data.json();
//         const filteredData = jsonData.filter((post) => {
//             return post.userId === id
//         })
//     }
//     catch(err) {
// console.log(err)
//     }
// }

// posts(0)


// Create a function that returns all comments from
// https://jsonplaceholder.typicode.com/comments
// whose email address ends with '.net'

// async function commentsWithEmail() {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/comments');
//         const jsonData = await data.json();
//         const filteredEmails = jsonData.filter((value) => {
//             return value.email.endsWith('.net')
//         })
//         filteredEmails.forEach((value) => {
//             console.log(value);
//         })
//     }
//     catch (err) {
//         console.log(err);
//     }
// }

// commentsWithEmail()



// setInterval(() => {
//     console.log('hello');

// }, 1 * 1000);

// console.log('world');
// const x = true;
// const resolvePromise = Promise.resolve('wow');
// const promise = new Promise((resolve, reject) => {
//     if (x === true) {
//         resolve('hello')
//     }
//     reject('x was not true')
// })


// promise
//     .then((data) => {
//         console.log(data);
//         return resolvePromise
//     })
//     .then(otherData => {
//         console.log(otherData);
//     })
//     .catch((err) => {
//         console.log(err);
//     })

// fetch('https://jsonplaceholder.typicode.com/users/1')
//     .then((data) => {
//         return data.json()})
//     .then(jsonData => console.log(jsonData))

// async function users() {
//     try {
//         const data = await fetch('https://jsonplaceholder.typicode.com/users/');
//         const jsonData = await data.json();
//         jsonData.forEach(user => {
//             console.log(user.name);
//         })
//     }
//     catch (err) {
//         console.log(err);
//     }
// }

// users().then()

// Create a function that receives a parameter of an id and
// fetches from https://jsonplaceholder.typicode.com/posts
// and logs all posts by that userId to the console

async function posts(id) {
    const posts = await fetch('https://jsonplaceholder.typicode.com/posts').then(data => data.json())
    const filteredPosts = posts
        .filter(post => {
            return post.userId === id
        })
        .forEach(post => {
            console.log(post);
        })

}
posts(1).then()