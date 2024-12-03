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

let x = 1;
while(x <= 10) {
    console.log(x++);
    // x++;
}

// 3. Write a JavaScript while loop that will iterate from 0
// to 15. For each iteration, it will check if the current
// number is odd or even, and display a message to
// the screen.

x = 0;
while(x <= 15) {
    if(x % 2 === 0) {
        console.log(x, 'even');
    }
    else {
        console.log(x, 'odd');
    }
    x++;
}

// 4. Write a JS code to print Even numbers in given array

const arr = [1,2,3,4,5,6,7,8,9,57,22];

let i = 0;

while(i < arr.length) {
    if(arr[i] % 2 === 0) {
        console.log(arr[i]);
    }
    i++;
}

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

let i = 1;
let str = '';

while (i <= 8) {
    str += i + ' '
    console.log(str);
    i++;
}

// 6. Write a JS code to find the number of digits in a
// number without turning it to a string

let num = 12345;
let digits = 0;
while (num >= 1) {
    digits++;
    num /= 10;
}
console.log(digits);


// 7. Write a JS code to find the largest number in an array

const findMax = (arr) => {
    let max = arr[0];
    arr.forEach(element => { if (element > max) max = element;});
    return max;
};

console.log(findMax([1, 2, 3, 4, 5]));


// 8. Write a JS code to print the Fibonacci series for a
// given value of N,  // example:  // fibonacci(8)   // Output:  // //0 1 1 2 3 5 8 13

const fibN = (N) => {
    let fib = [0, 1];
    for (let i = 1; i < N-3; i++) {
        fib.push(fib[i] + fib[i - 1]);
    }
    return fib;
};

// console.log(fibN(10));

// 9. Write a JS code to find N value in the Fibonacci series
// for a given number
// Example: findFibonacci(13) OutpuT:  "Element 13 is present in index 7"
// Example: findFibonacci(144) output:"Element 144 is present in index 12"

const fibN = (N) => {
    let a = 0; // F(0)
    let b = 1; // F(1)
    let index = 1; // Starting index for F(1)
    
    while (b < N) {
        let next = a + b; // Compute the next Fibonacci number
        a = b; // Move `b` to `a`
        b = next; // Update `b` to the next Fibonacci number
        index++; // Increment the index
    }
    
    return b === N ? index : -1; // Return index if found, else -1
};
console.log(`elem ${13} is present in index ${fibN(13)}`);
// Output: elem 13 is present in index 7

// 10. Bonus: Write a JS code for binary search algorithm
// The binary search algorithm is a highly efficient method for finding an item from a sorted array.
// It works by repeatedly dividing the search interval in half.
// If the value of the search key is less than the item in the middle of the interval,
// the interval is narrowed to the lower half. Otherwise, it is narrowed to the upper half.


const binarySearch = (arr, target) => {
    let left = 0; // Starting index
    let right = arr.length - 1; // Ending index

    while (left <= right) {
        // Find the middle index
        const mid = Math.floor((left + right) / 2);

        if (arr[mid] === target) {
            return mid; // Target found, return its index
        }

        if (arr[mid] < target) {
            left = mid + 1; // Search the right half
        } else {
            right = mid - 1; // Search the left half
        }
    }

    return -1; // Target not found
};

// Example usage:
const sortedArray = [1, 3, 5, 7, 9, 11, 13, 15];
const target = 7;
const result = binarySearch(sortedArray, target);

console.log(`Target ${target} is at index: ${result}`);
// Output: Target 7 is at index: 3



// ################################# EXTRA EX1 ######################################


// EX1. Write a function that takes an array of numbers and
// returns an array of the numbers squared. make it with an
// arrow function
// const arr = [1,2,3,4,5,6,7,8,9,57,22];

// ALTERNATIVE #1:
const squared_arr = (arr) => arr.map(element => element ** 2);

// ALTERNATIVE #2:
const squared_arr = (arr) => arr.map(element => Math.pow(element, 2));
console.log(squared_arr(arr));

// ALTERNATIVE #3:
const arr = [1, 2, 3, 4, 5];
const squaredArr = arr.reduce((accumulator, currentValue) => {
    accumulator.push(currentValue ** 2); // Square the current value and push to accumulator
    return accumulator;
}, []); // Start with an empty array as the initial value
console.log(squaredArr);


// EX2. Medium: Write a function that takes in an array of numbers and
// returns the average of the numbers.
        // use the reduce method for this. REDUCE: array.reduce(callback, initialValue)
        // callback: A function executed on each element. It takes four arguments:
        // Accumulator: The value being accumulated across iterations.
        // Current Value: The current element of the array.
        // Current Index: The index of the current element (optional).
        // Array: The array being traversed (optional).
        // initialValue: An optional initial value for the accumulator. If not provided, the first element of the array is used as the initial value.
// average([1, 2, 3]) //output 2.

const arr = [1, 2, 3, 4, 5];
const sum = arr.reduce((acc, currentValue) => {
    console.log(acc, currentValue);
    return acc + currentValue
}, 0);
const avg = sum / arr.length;

// EX3. Create an asynchronous function in JavaScript that takes an array of numbers and returns a new array .
// The function should iterate over the array and double each odd number, leaving even numbers unchanged .
// Use promises to simulate an asynchronous calculation while doubling the numbers

// ALTERNATIVE #1:
function doubleOddNumber(arr) {
    const newArr = [];
    for (const value of arr) {
        if (value % 2 !== 0) {
            newArr.push(value * 2);
        }
        else {
            newArr.push(value);
        }
    }
    return newArr;
}

// ALTERNATIVE #2:
const doubleOddNumber = (arr) => {
    return arr.map(element => element % 2 === 0 ? element : element*2);
};
console.log(doubleOddNumber([1, 2, 3, 4, 5]));


// ALTERNATIVE #3:
const doubleOddNumber = [1, 2, 3, 4, 5].reduce((accumulator, currentValue) => {
    accumulator.push(currentValue % 2 === 0 ? currentValue : currentValue*2); // Square the current value and push to accumulator
    return accumulator;
}, []); // Start with an empty array as the initial value
console.log(doubleOddNumber);


// ################################# ARRAY METHODS ######################################

// Example - Replacing elements ; arr.splice(start, deleteCount, ...itemsToAdd);
// const arr = [1, 2, 3, 4, 5];
// arr.splice(1, 2, 8, 9); // Replace 2 elements starting at index 1 with 8, 9
// console.log(arr); // Output: [1, 8, 9, 4, 5]


// Example - sort with a Comparator
// The sort method is used to sort an array. Without a comparator, it sorts elements as strings by default. To sort numerically, you need to provide a comparator function.
// Syntax:

arr.sort((a, b) => a - b); // Ascending order
arr.sort((a, b) => b - a); // Descending order

const arr = [5, 1, 4, 3, 2];
arr.sort((a, b) => b - a); // Sort numerically in descending order
console.log(arr); // Output: [5, 4, 3, 2, 1]


const people = [
    { name: 'Alice', age: 25 },
    { name: 'Bob', age: 22 },
    { name: 'Charlie', age: 30 },
];

// // Sort by age in ascending order
// people.sort((a, b) => a.age - b.age);

console.log(people);
Output:
[
  { name: 'Bob', age: 22 },
  { name: 'Alice', age: 25 },
  { name: 'Charlie', age: 30 }
]

// ### **Exercise 1: Name Initials**

const getInitials = (string) => {
    return string
        .split(' ') // Split the string into words
        .map(word => word[0]) // Get the first letter of each word
        .join(''); // Join the initials
};

const string = 'Peter Ingrid Tesla Amber';
console.log(getInitials(string)); // Output: 'PITA'


// ### **Exercise 2: Sum of Positives**

const sumOfPositives = (arr) => {
    return arr
        .filter(num => num > 0) // Keep only positive numbers
        .reduce((sum, num) => sum + num, 0); // Sum them up
};

console.log(sumOfPositives([-1, 2, 3, -4, 5])); // Output: 10
console.log(sumOfPositives([])); // Output: 0
console.log(sumOfPositives([-1, -2, -3])); // Output: 0

// ### **Exercise 3: Map Array to Object**

const mapArrayToObject = (arr, fn) => {
    return arr.reduce((obj, el) => {
        obj[el] = fn(el); // Map each element to its transformed value
        return obj;
    }, {});
};

const numbers = [1, 2, 3];
const squared = mapArrayToObject(numbers, x => x * x);

console.log(squared); // Output: { '1': 1, '2': 4, '3': 9 }


// ### **Exercise 4: Devs Numeronyms**

const abbreviateWords = (sentence) => {
    return sentence
        .split(' ') // Split the sentence into words, 1st space occurence is removed!
        .map(word => {
            if (word.length < 4) return word; // Keep short words as is
            const first = word[0];
            const last = word[word.length - 1];
            const middleCount = word.length - 2;
            return `${first}${middleCount}${last}`; // Abbreviate long words
        })
        .join(' '); // Reconstruct the sentence
};

const input = "Every developer likes to mix kubernetes and javascript";
console.log(abbreviateWords(input));
// Result: "E3y d7r l3s to mix k8s and j8t"


// ### **Exercise 5: Factorial Calculation**

const factorial = (n) => {
    if (n === 0) return 1; // Base case
    return n * factorial(n - 1); // Recursive case
};

console.log(factorial(6)); // Result: 720
console.log(factorial(0)); // Result: 1

// ### **Exercise 6: Count Distinct Elements in 2D Array**

const countDistinct = (matrix) => {
    return matrix
        .flat() // Flatten the 2D array into a 1D array
        .reduce((count, element) => {
            count[element] = (count[element] || 0) + 1; // Increment count
            return count;
        }, {}); // Start with an empty object!!! allows for iterations on distinct members,
        //once tackeled firstly! the accumulator is an object {} of a,b,c keys
};

const input = [
    ['a', 'b', 'c'],
    ['c', 'd', 'f'],
    ['d', 'f', 'g'],
];

console.log(countDistinct(input)); 
// Result: { a: 1, b: 1, c: 2, d: 2, f: 2, g: 1 }

// ################################# EXTRA EX2 ######################################


// 1. Check whether an input is an array
function is_array(input) {
    return Array.isArray(input);
  }
  
  console.log(is_array('w3resource')); // Output: false
  console.log(is_array([1, 2, 4, 0])); // Output: true
  
  
  // 2. Get the first element of an array, or the first 'n' elements
  function first(arr, n = 1) {
    return arr.slice(0, n);
  }
  
  console.log(first([7, 9, 0, -2])); // Output: [7]
  console.log(first([], 3)); // Output: []
  console.log(first([7, 9, 0, -2], 3)); // Output: [7, 9, 0]
  console.log(first([7, 9, 0, -2], 6)); // Output: [7, 9, 0, -2]
  console.log(first([7, 9, 0, -2], -3)); // Output: []
  
  
  // 3. Get the last element of an array, or the last 'n' elements
  function last(arr, n = 1) {
    return arr.slice(-n);
  }
  
  console.log(last([7, 9, 0, -2])); // Output: [-2]
  console.log(last([7, 9, 0, -2], 3)); // Output: [9, 0, -2]
  console.log(last([7, 9, 0, -2], 6)); // Output: [7, 9, 0, -2]
  
  
  // 4. Join all elements of an array into a string
  function joinArray(arr) {
    return arr.join(',');
  }
  
  let myColor = ["Red", "Green", "White", "Black"];
  console.log(joinArray(myColor)); // Output: "Red,Green,White,Black"
  
  
  // 5. Insert dashes between even numbers in a number string
  function insertDashes(num) {
    return num.replace(/([02468])(?=[02468])/g, '$1-');
  }
  
  console.log(insertDashes("025468")); // Output: "0-254-6-8"
  
  
  // 6. Find the most frequent item in an array
  function mostFrequent(arr) {
    let frequency = {};
    let maxCount = 0;
    let mostFrequentItem;
  
    arr.forEach(item => {
      frequency[item] = (frequency[item] || 0) + 1;
      if (frequency[item] > maxCount) {
        maxCount = frequency[item];
        mostFrequentItem = item;
      }
    });
  
    return `${mostFrequentItem} (${maxCount} times)`;
  }
  
  let arr1 = [3, 'a', 'a', 'a', 2, 3, 'a', 3, 'a', 2, 4, 9, 3];
  console.log(mostFrequent(arr1)); // Output: "a (5 times)"
  
  
  // 7. Sum the corresponding values of two arrays
  function sumArrays(arr1, arr2) {
    const maxLength = Math.max(arr1.length, arr2.length);
    const result = [];
  
    for (let i = 0; i < maxLength; i++) {
      result.push((arr1[i] || 0) + (arr2[i] || 0));
    }
  
    return result;
  }
  
  let array1 = [1, 0, 2, 3, 4];
  let array2 = [3, 5, 6, 7, 8, 13];
  console.log(sumArrays(array1, array2)); // Output: [4, 5, 8, 10, 12, 13]
  


// 8. Goal: Combine multiple arrays into one using the spread operator. . 
  let array1 = [1, 2]; 
  let array2 = [3, 4]; 
  let combined = [...array1, ...array2];


// 9. function rmi(i, arr) {
    // Remove the element at index `i` and return the modified array
    function rmi(i, arr) {
        // Remove the element at index `i` and return the modified array
        return arr.filter((_, idx) => idx !== i);
    }
    
    // Example usage
    const originalArray = [10, 20, 30, 40, 50];
    const newArray = rmi(2, originalArray); // Remove element at index 2
    console.log(newArray); // Output: [10, 20, 40, 50]
    

// 10. reate a function that takes two parameters: an array of numbers and an integer representing the number of steps to traverse .
    // Example usage:    const array = [1, 2, 3, 4, 5];    const steps = 2;    Output: [4, 5, 1, 2, 3]
    const array = [1, 2, 3, 4, 5];
    function circularTraversal(arr, steps) {
        if (!Array.isArray(arr) || typeof steps !== 'number') {
            throw new Error('Invalid input: first argument must be an array and second must be a number');
        }
    
        const length = arr.length;
        if (length === 0) return [];
    
        // Normalize the steps to avoid redundant cycles
        let normalizedSteps = steps % length;
    
        // Convert negative steps for counter-clockwise traversal
        if (normalizedSteps < 0) {
            normalizedSteps += length;
        }
    
        // Perform circular traversal
        const result = arr.slice(-normalizedSteps).concat(arr.slice(0, -normalizedSteps));
        return result;
    }
    
    // Example usage:
    const array = [1, 2, 3, 4, 5];    
    const stepsCounterClockwise = -2;
    console.log(circularTraversal(array, stepsCounterClockwise)); // Output: [3, 4, 5, 1, 2]
    
// ################################# ARRAY CHEATSHEET ######################################

// 1. concat()
const arr1 = [1, 2];
const arr2 = [3, 4];
console.log(arr1.concat(arr2)); // Output: [1, 2, 3, 4]

// 2. constructor
const arr = [1, 2, 3];
console.log(arr.constructor); // Output: [Function: Array]

// 3. copyWithin()
const arr3 = [1, 2, 3, 4, 5];
console.log(arr3.copyWithin(0, 3)); // Output: [4, 5, 3, 4, 5]

// 4. entries()
const arr4 = ['a', 'b', 'c'];
for (const [index, value] of arr4.entries()) {
  console.log(index, value); // Output: 0 'a', 1 'b', 2 'c'
}

// 5. every()
const arr5 = [1, 2, 3, 4];
console.log(arr5.every(n => n > 0)); // Output: true (all elements are greater than 0)

// 6. fill()
const arr6 = [1, 2, 3, 4];
console.log(arr6.fill(0)); // Output: [0, 0, 0, 0]

// 7. filter()
const arr7 = [1, 2, 3, 4, 5];
console.log(arr7.filter(n => n > 2)); // Output: [3, 4, 5]

// Combine filtering and mapping into a single operation
const arr7m = arr.filter(n => n > 2);

// 8. find()
const arr8 = [1, 2, 3, 4];
console.log(arr8.find(n => n > 2)); // Output: 3 (first element greater than 2)

// 9. findIndex()
const arr9 = [1, 2, 3, 4];
console.log(arr9.findIndex(n => n > 2)); // Output: 2 (index of first element greater than 2)

// 10. forEach()
const arr10 = [1, 2, 3];
arr10.forEach(n => console.log(n)); // Output: 1, 2, 3

// 11. from()
const obj = { 0: 'a', 1: 'b', length: 2 };
console.log(Array.from(obj)); // Output: ['a', 'b']

// 12. includes()
const arr11 = [1, 2, 3];
console.log(arr11.includes(2)); // Output: true

// 13. indexOf()
const arr12 = [1, 2, 3];
console.log(arr12.indexOf(2)); // Output: 1

// 14. isArray()
const arr13 = [1, 2, 3];
console.log(Array.isArray(arr13)); // Output: true

// 15. join()
const arr14 = ['a', 'b', 'c'];
console.log(arr14.join('-')); // Output: 'a-b-c'

// 16. keys()
const arr15 = ['a', 'b', 'c'];
for (const key of arr15.keys()) {
  console.log(key); // Output: 0, 1, 2
}

// 17. lastIndexOf()
const arr16 = [1, 2, 3, 2];
console.log(arr16.lastIndexOf(2)); // Output: 3

// 18. length
const arr17 = [1, 2, 3];
console.log(arr17.length); // Output: 3

// 19. map()
const arr18 = [1, 2, 3];
console.log(arr18.map(n => n * 2)); // Output: [2, 4, 6]

// 20. pop()
const arr19 = [1, 2, 3];
console.log(arr19.pop()); // Output: 3 (removes the last element)

// 21. prototype
Array.prototype.sayHello = function() {
  console.log('Hello from array!');
};
const arr20 = [1, 2, 3];
arr20.sayHello(); // Output: 'Hello from array!'

// 22. push()
const arr21 = [1, 2, 3];
console.log(arr21.push(4)); // Output: 4 (new length of the array)

// 23. reduce()
const arr22 = [1, 2, 3];
console.log(arr22.reduce((sum, n) => sum + n, 0)); // Output: 6 (sum of all elements)

// 24. reduceRight()
const arr23 = [1, 2, 3];
console.log(arr23.reduceRight((sum, n) => sum + n, 0)); // Output: 6 (sum of all elements from right to left)

// 25. reverse()
const arr24 = [1, 2, 3];
console.log(arr24.reverse()); // Output: [3, 2, 1]

// 26. shift()
const arr25 = [1, 2, 3];
console.log(arr25.shift()); // Output: 1 (removes the first element)

// 27. slice()
const arr26 = [1, 2, 3, 4];
console.log(arr26.slice(1, 3)); // Output: [2, 3] (subarray from index 1 to 2)

// 28. some()
const arr27 = [1, 2, 3];
console.log(arr27.some(n => n > 2)); // Output: true (at least one element is greater than 2)

// 29. sort()
const arr28 = [3, 1, 2];
console.log(arr28.sort((a, b) => a - b)); // Output: [1, 2, 3] (sorted ascending)

// 30. splice()
const arr29 = [1, 2, 3, 4];
arr29.splice(1, 2, 'a', 'b');
console.log(arr29); // Output: [1, 'a', 'b', 4] (removes 2 elements and adds 'a' and 'b')

// 31. toString()
const arr30 = [1, 2, 3];
console.log(arr30.toString()); // Output: '1,2,3' (array as string)

// 32. unshift()
const arr31 = [1, 2, 3];
console.log(arr31.unshift(0)); // Output: 4 (new length of the array)

// 33. valueOf()
const arr32 = [1, 2, 3];
console.log(arr32.valueOf()); // Output: [1, 2, 3] (returns the array itself)

