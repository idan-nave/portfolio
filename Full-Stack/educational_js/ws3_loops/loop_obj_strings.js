// Exercise: Given the following string: “ 123Hello45 “
// create a function that returns the following: [h,e,l,l,o]

// ALTERNATIVE #1:
const extractLetters = (str) => {
    // Initialize an empty array to store the alphabetic characters
    let result = [];
  
    // Loop through each character in the string
    for (let i = 0; i < str.length; i++) {
      // If the character is alphabetic, add it to the result array
      if (str[i].isalpha()) {
        result.push(str[i].toLowerCase()); // Push the letter in lowercase
      }
    }
    
    return result;
  };
  
  // Test the function with the given string
  const input = " 123Hello45 ";
  console.log(extractLetters(input)); 
  Output: ['h', 'e', 'l', 'l', 'o']
  

// ALTERNATIVE #2:
const extractLetters = (str) => 
    [...str].filter(char => char.isAlpha()).map(char => char.toLowerCase());
  
  // Test the function with the given string
  const input = " 123Hello45 ";
  console.log(extractLetters(input)); 
  Output: ['h', 'e', 'l', 'l', 'o']
  

// ################################# STRING METHODS ######################################

//1. Write a function that takes a string and returns a new
// string with all of the characters in the original string
// reversed.

console.log(reverseString('hello')); / Output: 'olleh'

const string = 'hello world'

console.log(string.slice(0, 4));

function reverseString(string) {
    let newString = ''
    for (let i = string.length - 1; i >= 0; i--) {
        // console.log(string.charAt(i));
        newString += string.charAt(i);
        console.log(newString);

    }
    console.log(newString);
}

reverseString(string)

// 2. Write a function that takes an array of objects and a
// property name, and returns an array of the values of the
// specied property for each object.

const books = [ { title: 'The Great Gatsby', pages: 180 }, { title: 'To Kill
    a Mockingbird', pages: 280 }, { title: 'Pride and Prejudice', pages: 150
    } ]; console.log(getPropertyValues(books, 'pages')); / Output: [180,
    280, 150]


const books = [
    { title: 'The Great Gatsby', pages: 180 },
    { title: 'To Killa Mockingbird', pages: 280 },
    { title: 'Pride and Prejudice', pages: 150 }
];

function getPropertyValues(arr, property) {
    const newArr = [];
    for (const object of arr) {
        newArr.push(object[property])
    }
    return newArr
}

console.log(getPropertyValues(books, ''));


// 3. Medium: Write a function that takes in a string and returns an
// array of all the words in the string.

stringToArray("hello world, I am Armadillo") //output
["hello", "world", "I", "am", "Armadillo"]

function getSentenceWords(string) {
    const newString = string.replace(',', '').split(' ')
    return newString.split(' ')
}

const string = "Hello world this, is a simple test";
console.log(getSentenceWords(string));

//used to traverse objects
const obj ={
    name: 'nitay'
}
for (const key in obj) {
    console.log(key); // name
    console.log(obj[key]); //nitay
} //will run for every key


// 4. Easy: Write a function that takes in a string and returns the
// string with all vowels removed.
// For example,
// removeVowels("hello") //output hll.


function removeVowels(str) {
    const arr = str.split('');
    const func = (char, index) => {
        if (char === 'a' | char === 'e' | char === 'o' | char === 'i' | char === 'u') {
            return false
        }
        return true
    }
    const filteredArray = arr.filter(func)
    return filteredArray.join('')
}

console.log(removeVowels('hello'))


// 5. Hard: Write a function that takes in an array of strings and
// returns an array of the strings sorted by length, with the
// shortest strings first. Use the sort method

sortedStrings("hello world, I am Armadillo")//output
["I", "am", "hello", "world", "Armadillo"]

const arr = "hello world, I am Armadillo".split(' ')
const arr = ['hello', 'world,', 'I', 'am', 'Armadillo'];
console.log(arr.sort((a, b) => a.length - b.length));

let string = "hello world, I am Armadillo";
function sortByLength(string) {
    return string.split(' ').sort((a, b) => a.length - b.length);
}

console.log(sortByLength(string))


// 6. Medium: Write a function that takes in a string and returns the
// string with all characters in reverse order.
// For example,
// reverseString("hello") //output olleh.

function reverseString(str) {
    return str
        .split('')
        .sort(() => -1) // OR         .reverse() // Reverse the array
        .join('')
}
const arr = [1, 25, 2, 5, 1]
arr.sort((a, b) => a - b);
console.log(reverseString('hello'));

// 6. Easy: Replace all occurrences of 'a' with 'z'
function aToZ(str) {
    return str.replace(/a/g, 'z');
  }
  
  console.log(aToZ("I am an Armadillo")); // Output: "I zm zn Zrmzdilo"
  
  
  // 7. Medium: Convert string into an array of words
  function stringToArray(str) {
    return str.split(' ');
  }
  
  console.log(stringToArray("hello world, I am Armadillo")); // Output: ["hello", "world,", "I", "am", "Armadillo"]
  
  
  // 8. Hard: Sort array of strings by length (shortest first)
  function sortedStrings(str) {
    const words = str.split(' ');
    return words.sort((a, b) => a.length - b.length);
  }
  
  console.log(sortedStrings("hello world, I am Armadillo")); // Output: ["I", "am", "hello", "world,", "Armadillo"]
  
  
  // 9. Easy: Capitalize the first letter of a string
  function upperCase(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
  }
  
  console.log(upperCase("hello")); // Output: "Hello"
  
  
  // 10. Medium: Find the minimum value in an array of numbers
  function minNum() {
    return Math.min.apply(null, arguments);
  }
  
  console.log(minNum(5, 8, 3, 78, 2, 1, 8, 5)); // Output: 1
  
  
  // 11. Medium: Join an array of strings into a single string
  function separator(arr) {
    return arr.join(' ');
  }
  
  console.log(separator(["hello", "world"])); // Output: "hello world"
  
  
  // 12. Hard: Find the second-largest number in an array of numbers
  function secondLargest(arr) {
    arr.sort((a, b) => a - b);
    return arr[arr.length - 2];
  }
  
  console.log(secondLargest([1, 2, 3, 4, 5, 6, 7])); // Output: 6
  
  
  // 13. Medium: Calculate the sum of all elements in an array
  function sumOf(arr) {
    return arr.reduce((acc, curr) => acc + curr, 0);
  }
  
  console.log(sumOf([1, 2, 3, 4, 5])); // Output: 15
  
  
  // 14. Medium: Get all words of even length from a string
  function arrOfAllWords(str) {
    return str.split(' ').filter(word => word.length % 2 === 0);
  }
  
  console.log(arrOfAllWords("hi world")); // Output: ["hi"]
  
  
  // 15. Hard: Sort an array of strings alphabetically, except for 'z' starting words
  function withoutZ(arr) {
    return arr.sort((a, b) => {
      if (a.startsWith('z') && !b.startsWith('z')) return 1;
      if (!a.startsWith('z') && b.startsWith('z')) return -1;
      return a.localeCompare(b);
    });
  }
  
  console.log(withoutZ(["hello", "world", "zero", "one"])); // Output: ["hello", "one", "zero", "world"]
  


// ################################# STRING CHEATSHEET ######################################


const str = "Hello World";

// 1. charAt()
console.log(str.charAt(1)); // Output: 'e'

// 2. charCodeAt()
console.log(str.charCodeAt(1)); // Output: 101 (Unicode of 'e')

// 3. concat()
console.log(str.concat("!")); // Output: 'Hello World!'

// 4. endsWith()
console.log(str.endsWith("World")); // Output: true

// 5. fromCharCode()
console.log(String.fromCharCode(72)); // Output: 'H' (Unicode 72 is 'H')

// 6. includes()
console.log(str.includes("World")); // Output: true

// 7. indexOf()
console.log(str.indexOf("o")); // Output: 4 (first occurrence of 'o')

// 8. lastIndexOf()
console.log(str.lastIndexOf("o")); // Output: 7 (last occurrence of 'o')

// 9. localeCompare()
console.log("apple".localeCompare("banana")); // Output: -1 (apple comes before banana)

// 10. match()
console.log(str.match(/l/g)); // Output: ['l', 'l'] (matches 'l' twice)

// 11. repeat()
console.log("Hello ".repeat(3)); // Output: 'Hello Hello Hello '

// 12. replace()
console.log(str.replace("World", "Universe")); // Output: 'Hello Universe'

// 13. search()
console.log(str.search("o")); // Output: 4 (index of first 'o')

// 14. slice()
console.log(str.slice(0, 5)); // Output: 'Hello'

// 15. split()
console.log(str.split(" ")); // Output: ['Hello', 'World']

// 16. startsWith()
console.log(str.startsWith("Hello")); // Output: true

// 17. substr()
console.log(str.substr(0, 5)); // Output: 'Hello'

// 18. substring()
console.log(str.substring(0, 5)); // Output: 'Hello'

// 19. toLocaleLowerCase()
console.log(str.toLocaleLowerCase()); // Output: 'hello world'

// 20. toLocaleUpperCase()
console.log(str.toLocaleUpperCase()); // Output: 'HELLO WORLD'

// 21. toLowerCase()
console.log(str.toLowerCase()); // Output: 'hello world'

// 22. toString()
const num = 123;
console.log(num.toString()); // Output: '123'

// 23. toUpperCase()
console.log(str.toUpperCase()); // Output: 'HELLO WORLD'

// 24. trim()
console.log("  Hello World  ".trim()); // Output: 'Hello World'

// 25. valueOf()
console.log(str.valueOf()); // Output: 'Hello World' (string primitive value)
