// Here’s how to use `for-in` and `for-of` loops with objects and arrays, including examples and explanations of when to use each.

// ### **For-In Loop**
// **Purpose**: Iterates over the **keys** of an object or the **indices** of an array.

// #### Example with an Object:
let obj = { a: 1, b: 2, c: 3 };

for (let key in obj) {
  console.log(`Key: ${key}, Value: ${obj[key]}`);
}
// Output:
// Key: a, Value: 1
// Key: b, Value: 2
// Key: c, Value: 3


// #### Example with an Array:
let arr = [10, 20, 30];

for (let index in arr) {
  console.log(`Index: ${index}, Value: ${arr[index]}`);
}
// Output:
// Index: 0, Value: 10
// Index: 1, Value: 20
// Index: 2, Value: 30

//  #### Example with strings:
// for-in iterates over the indices (positions) of a string.
let str = "hello";

for (let index in str) {
  console.log(`Index: ${index}, Character: ${str[index]}`);
}
// Output:
// Index: 0, Character: h
// Index: 1, Character: e
// Index: 2, Character: l
// Index: 3, Character: l
// Index: 4, Character: o


// ### **For-Of Loop**
// **Purpose**: Iterates over the **values** of an iterable (like an array, strings, or other iterable objects). Does not work directly with plain objects.

// #### Example with an Object:
// To use `for-of` with an object, you need to get its keys, values, or entries (using `Object.keys`, `Object.values`, or `Object.entries`):
let obj = { a: 1, b: 2, c: 3 };

for (let [key, value] of Object.entries(obj)) {
  console.log(`Key: ${key}, Value: ${value}`);
}
// Output:
// Key: a, Value: 1
// Key: b, Value: 2
// Key: c, Value: 3


// #### Example with an Array:
let arr = [10, 20, 30];

for (let value of arr) {
  console.log(`Value: ${value}`);
}
// Output:
// Value: 10
// Value: 20
// Value: 30


//  #### Example with strings:
//  for-of iterates over the characters of a string.
let str = "hello";

for (let char of str) {
  console.log(`Character: ${char}`);
}
// Output:
// Character: h
// Character: e
// Character: l
// Character: l
// Character: o



// ### **Key Differences Between For-In and For-Of**

// | Feature                | For-In                        | For-Of                                           |
// ||-|-|
// | Iterates Over          | Object keys or array indices  | Array or iterable values                         |
// | Use Case with Objects  | Yes, works with object keys   | Requires `Object.entries` or similar             |
// | Use Case with Arrays   | Yes, iterates over indices    | Yes, iterates over values                        |
// | Use Case with Strings  | Access characters by index    | Yes, iterates over chars                         |
// | Returns                | String keys (for objects) or indices (for arrays) | Values of iterable elements  |



// ### **Combined Example**
let obj = { a: 1, b: 2, c: 3 };
let arr = [10, 20, 30];

// For-In with Object
console.log("For-In with Object:");
for (let key in obj) {
  console.log(`Key: ${key}, Value: ${obj[key]}`);
}

// For-Of with Object
console.log("\nFor-Of with Object:");
for (let [key, value] of Object.entries(obj)) {
  console.log(`Key: ${key}, Value: ${value}`);
}

// For-In with Array
console.log("\nFor-In with Array:");
for (let index in arr) {
  console.log(`Index: ${index}, Value: ${arr[index]}`);
}

// For-Of with Array
console.log("\nFor-Of with Array:");
for (let value of arr) {
  console.log(`Value: ${value}`);
}

let str = "world";

// For-In: Iterating over indices
console.log("For-In with String:");
for (let index in str) {
  console.log(`Index: ${index}, Character: ${str[index]}`);
}

// For-Of: Iterating over characters
console.log("\nFor-Of with String:");
for (let char of str) {
  console.log(`Character: ${char}`);
}


// ### Output:
// For-In with Object:
// Key: a, Value: 1
// Key: b, Value: 2
// Key: c, Value: 3

// For-Of with Object:
// Key: a, Value: 1
// Key: b, Value: 2
// Key: c, Value: 3

// For-In with Array:
// Index: 0, Value: 10
// Index: 1, Value: 20
// Index: 2, Value: 30

// For-Of with Array:
// Value: 10
// Value: 20
// Value: 30

// For-In with String:
// Index: 0, Character: w
// Index: 1, Character: o
// Index: 2, Character: r
// Index: 3, Character: l
// Index: 4, Character: d

// For-Of with String:
// Character: w
// Character: o
// Character: r
// Character: l
// Character: d
