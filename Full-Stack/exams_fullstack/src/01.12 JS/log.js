// console.log('1' == 1);

// console.log(true ? 'Yes' : 'No');

// console.log(1)
// console.log(2)
// setTimeout(() => console.log(3), 0)
// console.log(4)
// console.log(5)

//Create a function that receives an array of numbers as a parameter and returns the number of even numbers in the array.
// function countEven(arr) {
//     if (arr === null) return -1;
//     let c = 0;
//     arr.forEach(item => {
//         if (item % 2 == 0) {
//             c += 1;
//         }
//     });
//     return c;
// }

// console.log(countEven([1, 2, 6, 9, 4, 0])); //includes 0




// function findLargestWord(inputText) {
//     let words = inputText.split(' ');
//     let max = 0;
//     let largest = '';

//     words.forEach(word => {
//         let wordLength = word.length;
//         if (wordLength > max) {
//             largest = word;
//             max = wordLength;
//         }
//     });

//     return largest; 
// }

// console.log(findLargetWord("f fsdfd df fdf fd")); //includes 0



// ##########################################################
// function primesUpto(upto) {
//     if (typeof upto !== 'number' || upto < 2) {
//         console.log("invalid input. must be >= 2.");
//         return;
//     }

//     function isPrime(num) {
//         if (num < 2) return false;
//         for (let i = 2; i <= Math.sqrt(num); i++) {
//             if (num % i === 0) return false;
//         }
//         return true;
//     }

//     //print promes up to upto:
//     for (let i = 2; i <= upto; i++) {
//         if (isPrime(i)) {
//             console.log(i);
//         }
//     }
// }

// console.log(primesUpto(15));

// ##########################################################
// Write a JavaScript function that takes a string as input and returns the string with each word reversed while maintaining the order of the words.
// Example:// Input: Hello world, how are you?
// Output: olleH dlrow, woh era ?uoy

// function revWordsNotOrder(str) {
//     let words = str.split(' ');
//     let after_rev = words.map(word => reverseString(word)); 
//     // console.log(after_rev); 
//     return after_rev.join(' '); 
// }

// function reverseString(string) {
//     let newString = '';
//     for (let i = string.length - 1; i >= 0; i--) {
//         newString += string.charAt(i); 
//     }
//     return newString;
// }

// console.log(revWordsNotOrder("Hello world, how are you?"));



// ##########################################################
// Write a function that receives an array as a parameter,
// Returns an array with only the numbers and sorted.

// function sortRem(arr) {

//     // filter alphas
//     let nums = arr.filter(item => typeof item === 'number');
//     nums.sort((a, b) => a - b);

//     return nums;
// }


// Create an html page with a button and a list, when clicking on the button, perform a fetch request to the following API - 
// https://jsonplaceholder.typicode.com/
// And display 5, random emails from the API in a list, on the html page.


async function fetcher() {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/users');

        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const data = await response.json();

        // console.log(data);// all of json 

        const emails = data
            .sort(() => 0.5 - Math.random()) // Shuffle array
            .slice(0, 5) // minimize to 5 emails
            .map(user => user.email); // Extract emails

        console.log(emails);// all of json 

        // // Display the emails in the list
        // emails.forEach(email => {
        //     const listItem = document.createElement('li');
        //     listItem.textContent = email;
        //     emailList.appendChild(listItem);
        // });
    } catch (error) {
        console.error('Error fetching data:', error);
    }
}

fetcher();