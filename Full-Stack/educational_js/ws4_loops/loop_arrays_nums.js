// let count = 0

// while (count < 50) {
//     count++;
// } //runs 50 times

// count = 0
// do {
//     //will run once
// } while (count > 0);

//While exercises
    
// 1. Write a JS code to print numbers from 1 to 10

// let x = 1;
// while(x <= 10) {
//     console.log(x++);
//     // x++;
// }

// 3. Write a JavaScript while loop that will iterate from 0
// to 15. For each iteration, it will check if the current
// number is odd or even, and display a message to
// the screen.

// x = 0;
// while(x <= 15) {
//     if(x % 2 === 0) {
//         console.log(x, 'even');
//     }
//     else {
//         console.log(x, 'odd');
//     }
//     x++;
// }

// 4. Write a JS code to print Even numbers in given array

// const arr = [1,2,3,4,5,6,7,8,9,57,22];

// let i = 0;

// while(i < arr.length) {
//     if(arr[i] % 2 === 0) {
//         console.log(arr[i]);
//     }
//     i++;
// }

// 5. Write a JS code to print the following pattern using for
// loop
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5
// 1 2 3 4 5 6
// 1 2 3 4 5 6 7
// 1 2 3 4 5 6 7 8

// let i = 1;
// let str = '';

// while (i <= 8) {
//     str += i + ' '
//     console.log(str);
//     i++;
// }

// 6. Write a JS code to find the number of digits in a
// number without turning it to a string

let num = 12345;
// let digits = 0;
// while (num >= 1) {
//     digits++;
//     num /= 10;
// }
// console.log(digits);


// 7. Write a function that takes an array of numbers and
// returns an array of the numbers squared. make it with an
// arrow function

// console.log(square([1, 2, 3, 4])); / Output: [1, 4, 9, 16]

// const square = (arr) => {
//     const func = (value, index) => {
//         if (index !== 2) {
//             return value * value
//         }
//         return value
//     }
//     return arr.map(func)
// }

// console.log(square([1, 2, 3, 4]));

// 8. Medium: Write a function that takes in an array of numbers and
// returns the average of the numbers.
// For example,
// use the reduce method for this
// average([1, 2, 3]) //output 2.

// const arr = [1, 2, 3, 4, 5];
// const sum = arr.reduce((acc, currentValue) => {
//     console.log(acc, currentValue);
//     return acc + currentValue
// }, 0);

// const avg = sum / arr.length;


// 9. Medium: Write a function that takes in a string and returns the
// string with all characters in reverse order.
// For example,
// reverseString("hello") //output olleh.

function reverseString(str) {
    return str
        .split('')
        .sort(() => 1)
        .join('')
}

const arr = [1, 25, 2, 5, 1]

arr.sort((a, b) => a - b);

console.log(reverseString('hello'));


// 10. Create an asynchronous function in JavaScript that takes an array of numbers and returns a new array .
// The function should iterate over the array and double each odd number, leaving even numbers unchanged .
// Use promises to simulate an asynchronous calculation while doubling the numbers

// function doubleOddNumber(arr) {
//     const newArr = [];
//     for (const value of arr) {
//         if (value % 2 !== 0) {
//             newArr.push(value * 2)
//         }
//         else {
//             newArr.push(value)
//         }
//     }
//     return newArr
// }

// console.log(doubleOddNumber([1, 2, 3, 4, 5]));

