//1. Write a function that takes a string and returns a new
// string with all of the characters in the original string
// reversed.

//console.log(reverseString('hello')); / Output: 'olleh'

// const string = 'hello world'

// console.log(string.slice(0, 4));

// function reverseString(string) {
//     let newString = ''
//     for (let i = string.length - 1; i >= 0; i--) {
//         // console.log(string.charAt(i));
//         newString += string.charAt(i);
//         console.log(newString);

//     }
//     console.log(newString);
// }

// reverseString(string)

// 2. Write a function that takes an array of objects and a
// property name, and returns an array of the values of the
// specied property for each object.

// const books = [ { title: 'The Great Gatsby', pages: 180 }, { title: 'To Kill
//     a Mockingbird', pages: 280 }, { title: 'Pride and Prejudice', pages: 150
//     } ]; console.log(getPropertyValues(books, 'pages')); / Output: [180,
//     280, 150]


// const books = [
//     { title: 'The Great Gatsby', pages: 180 },
//     { title: 'To Killa Mockingbird', pages: 280 },
//     { title: 'Pride and Prejudice', pages: 150 }
// ];

// function getPropertyValues(arr, property) {
//     const newArr = [];
//     for (const object of arr) {
//         newArr.push(object[property])
//     }
//     return newArr
// }

// console.log(getPropertyValues(books, ''));


// 3. Medium: Write a function that takes in a string and returns an
// array of all the words in the string.

// stringToArray("hello world, I am Armadillo") //output
// ["hello", "world", "I", "am", "Armadillo"]

// function getSentenceWords(string) {
//     const newString = string.replace(',', '').split(' ')
//     return newString.split(' ')
// }

// const string = "Hello world this, is a simple test";
// console.log(getSentenceWords(string));

// //used to traverse objects
// const obj ={
//     name: 'nitay'
// }
// for (const key in obj) {
//     console.log(key); // name
//     console.log(obj[key]); //nitay
// } //will run for every key


// 4. Easy: Write a function that takes in a string and returns the
// string with all vowels removed.
// For example,
// removeVowels("hello") //output hll.


// function removeVowels(str) {
//     const arr = str.split('');
//     const func = (char, index) => {
//         if (char === 'a' | char === 'e' | char === 'o' | char === 'i' | char === 'u') {
//             return false
//         }
//         return true
//     }
//     const filteredArray = arr.filter(func)
//     return filteredArray.join('')
// }

// console.log(removeVowels('hello'))


// 5. Hard: Write a function that takes in an array of strings and
// returns an array of the strings sorted by length, with the
// shortest strings first. Use the sort method

// sortedStrings("hello world, I am Armadillo")//output
// ["I", "am", "hello", "world", "Armadillo"]

// const arr = "hello world, I am Armadillo".split(' ')
const arr = ['hello', 'world,', 'I', 'am', 'Armadillo'];
console.log(arr.sort((a, b) => a.length - b.length));

let string = "hello world, I am Armadillo";
function sortByLength(string) {
    return string.split(' ').sort((a, b) => a.length - b.length);
}

console.log(sortByLength(string))
