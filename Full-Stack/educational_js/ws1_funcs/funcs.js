// 1. Create an empty array and log it to the console.
let emptyArray = [];
console.log(emptyArray);

// 2. Create an object with three key-value pairs and log it to the console.
let obj = { key1: "value1", key2: "value2", key3: "value3" };
console.log(obj);

// 3. Create an array with three elements and log the first element to the console.
let arr = [10, 20, 30];
console.log(arr[0]);

// 4. Create an object with a nested object inside it and log one of the nested object's values to the console.
let nestedObj = { outerKey: { innerKey: "innerValue" } };
console.log(nestedObj.outerKey.innerKey);

// 5. Create an array with at least five elements and log its length to the console.
let longArray = [1, 2, 3, 4, 5];
console.log(longArray.length);

// 6. Create an object with at least five key-value pairs and log the value of one of its keys to the console.
let bigObj = { a: 1, b: 2, c: 3, d: 4, e: 5 };
console.log(bigObj.c);

// 7. Create an array with at least three elements and an object with at least three key-value pairs. Use both to log a sentence to the console.
let arr2 = ["apple", "banana", "cherry"];
let obj2 = { x: "is red", y: "is yellow", z: "is red too" };
console.log(`${arr2[0]} ${obj2.x}`);

// 8. Define a function that takes two arguments and returns their sum.
function addNumbers(a, b) {
  return a + b;
}
console.log(addNumbers(5, 10));

// 9. Define a function that takes an array as an argument and consoles the second index of the array.
function logSecondIndex(array) {
  console.log(array[2]);
}
logSecondIndex([100, 200, 300]);

// 10. Define a function that takes an object as an argument and consoles the value of the second key in the object.
function logSecondKeyValue(obj) {
  let keys = Object.keys(obj);
  console.log(obj[keys[1]]);
}
logSecondKeyValue({ first: "A", second: "B", third: "C" });

// 11. Define a function that takes an array of 3 numbers as an argument and returns the sum of all the numbers in the array.
function sumArray(arr) {
  return arr[0] + arr[1] + arr[2];
}
console.log(sumArray([1, 2, 3]));

// 12. Define a function that receives an object with 2 keys and an array with 2 values. The function should console the sum of the second value and the second key.
function sumSecondKeyAndValue(obj, array) {
  let keys = Object.keys(obj);
  console.log(obj[keys[1]] + array[1]);
}
sumSecondKeyAndValue({ x: 10, y: 20 }, [1, 2]);

// ##################################### PRINTS #################################################

// // 1. Empty array
// []

// // 2. Object with three key-value pairs
// { key1: 'value1', key2: 'value2', key3: 'value3' }

// // 3. First element of an array
// 10

// // 4. Value from nested object
// innerValue

// // 5. Length of an array with five elements
// 5

// // 6. Value of a specific key in an object
// 3

// // 7. Sentence combining array and object
// apple is red

// // 8. Sum of two numbers
// 15

// // 9. Second index of an array
// 300

// // 10. Value of the second key in an object
// B

// // 11. Sum of three numbers in an array
// 6

// // 12. Sum of the second value and the second key
// 22
