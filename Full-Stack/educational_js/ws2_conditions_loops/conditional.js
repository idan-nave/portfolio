// 1. Boolean variable with if-else statement
const x = true;
if (x) {
  console.log('beep');
} else {
  console.log('bop');
}
// beep

// 2. Function to log true if arguments are equal
function checkEquality(arg1, arg2) {
  if (arg1 === arg2) {
    console.log(true);
  }
}
checkEquality(5, 5); // true


// 3. Function to log "beep" if first argument is greater, "bop" otherwise
function compareArguments(arg1, arg2) {
  if (arg1 > arg2) {
    console.log('beep');
  } else {
    console.log('bop');
  }
}
compareArguments(10, 5); // beep


// 4. Function with ternary operator for comparison
function compareWithTernary(arg1, arg2) {
  console.log(arg1 > arg2 ? 'beep' : 'bop');
}
compareWithTernary(3, 7);  // bop

// 5. Check x, y, z conditions
let x1 = 5, y = 3, z = 2;
if (x1 > 4) {
  console.log(x1 + y + z);
} else {
  console.log(x1 - y - z);
}
// 10 (if x1 = 5, y = 3, z = 2)

// 6. Function to check the fifth index in an array
function checkFifthIndex(arr) {
  if (arr[5] !== undefined) {
    console.log(arr[5]);
  } else {
    console.log('Fifth index does not exist.');
  }
}
checkFifthIndex([1, 2, 3, 4]); // Fifth index does not exist.


// 7. Function with scoped variables and count logic
function scopeCheck() {
  let x2 = 5, y2 = 5;
  let count = 10;
  if (x2 === y2) {
    count *= count;
  } else {
    count /= 2;
  }
  console.log(count);
}
scopeCheck(); // 100


// 8. Function to find the largest of 5 numbers
function findLargest(a, b, c, d, e) {
  if (a > b && a > c && a > d && a > e) {
    console.log(a);
  } else if (b > c && b > d && b > e) {
    console.log(b);
  } else if (c > d && c > e) {
    console.log(c);
  } else if (d > e) {
    console.log(d);
  } else {
    console.log(e);
  }
}
findLargest(3, 5, 2, 8, 7); // 8


// 9. Function to check for "name" key using a ternary operator
function checkNameKey(obj) {
  console.log(obj.name ? obj.name : 'No name key found.');
}
checkNameKey({ name: 'Alice' }); // Alice


// 10. Function to check if a number is even or odd, modify object
function addEvenOrOdd(num, obj) {
  num % 2 === 0 
    ? (obj.even = num) 
    : (obj.odd = num);
  console.log(obj);
}
addEvenOrOdd(7, {}); // { odd: 7 }


// // BONUS: Function to process array based on the second index:
// BONUS:
// make a function that receives an array as an argument, the argument can be of any type
// (string, boolean, number...). In case the second index of the array is a number, remove the
// first 3 elements in the array. else, remove the last 2 elements of the array.
function processArray(arr) {
  if (typeof arr[2] === 'number') {
    arr.splice(0, 3);
  } else {
    arr.splice(-2); //array.splice(start {- = from last}, deleteCount);

  }
  console.log(arr);
}
processArray([1, 2, 3, 4, 5]); // [4, 5] (array after processing [1, 2, 3, 4, 5])

processArray(['a', 'b', 'c', 'd']); // ['a', 'b'] (array after processing ['a', 'b', 'c', 'd'])
