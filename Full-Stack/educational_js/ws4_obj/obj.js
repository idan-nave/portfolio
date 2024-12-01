// Object.keys()
const obj7 = { name: 'Jake', age: 28 };
console.log(Object.keys(obj7)); // ['name', 'age']

// Object.values()
const person2 = { firstName: 'John', lastName: 'Doe' };
console.log(Object.values(person2)); // ['John', 'Doe']

// 1. Get the Length of the Object
let obj = {
  name: 'Charizard',
  type: 'fire'
};
console.log(Object.keys(obj).length);  // Output: 2

// 2. Using Object.keys() and Array.forEach()
let data = {
  real_name: 'Donald Glover',
  character_name: 'Troy Barnes',
  series: 'Community'
};

Object.keys(data).forEach(item => {
  console.log(item);
});
// Output:
// real_name
// character_name
// series

// 3. Sorting Objects by Keys
let unorderedData = {
  real_name: 'Donald Glover',
  character_name: 'Troy Barnes',
  series: 'Community'
};

const orderedData = {};
Object.keys(unorderedData).sort().forEach(function(key) {
  orderedData[key] = unorderedData[key];
});

console.log(JSON.stringify(orderedData));
// Output: {"character_name":"Troy Barnes","real_name":"Donald Glover","series":"Community"}

// 4. Using Object.entries()
const objEntries = { name: "Yonatan", age: 25, location: "Israel" };
console.log(Object.entries(objEntries));
// Output: [ [ 'name', 'Yonatan' ], [ 'age', 25 ], [ 'location', 'Israel' ] ]

// Iterating through key-value pairs
for (const [key, value] of Object.entries(objEntries)) {
  console.log(`${key}: ${value}`);
}
// Output:
// name: Yonatan
// age: 25
// location: Israel

// string -> from ES2015+, non-objects are coerced to object
const string = "code";
console.log(Object.entries(string)); // [ [ '0', 'c' ], [ '1', 'o' ], [ '2', 'd' ], [ '3', 'e' ] ]
// primitive types have no properties
console.log(Object.entries(55)); //


// 5. Using Object.values()
const person = {
  firstName: 'John',
  lastName: 'Doe',
  age: 25
};
const profile = Object.values(person);
console.log(profile);  // Output: [ 'John', 'Doe', 25 ]

// 6. Using Object.is()- used to compare two values to check if they are the same.
//It works similarly to ===, but it handles special cases like NaN and +0 vs -0 differently.
console.log(Object.is(25, 25));   // Output: true
console.log(Object.is(25, '25')); // Output: false
console.log(Object.is(NaN, NaN)); // Output: true
console.log(Object.is(0, -0));    // Output: false

// ################################# OBJECT CHEATSHEET ######################################

// Object.assign()
const target = { name: 'John' };
const source = { age: 30 };
Object.assign(target, source);
console.log(target); // { name: 'John', age: 30 }

// Object.create()
const prototype = { greet: function() { console.log('Hello!'); } };
const obj = Object.create(prototype);
obj.greet(); // Hello!

// Object.defineProperty()
const person = {};
Object.defineProperty(person, 'name', {
  value: 'Alice',
  writable: false
});
console.log(person.name); // Alice

// Object.defineProperties()
const car = {};
Object.defineProperties(car, {
  model: {
    value: 'Tesla',
    writable: true
  },
  year: {
    value: 2021,
    writable: false
  }
});
console.log(car); // { model: 'Tesla', year: 2021 }

// Object.entries()
const obj1 = { name: 'Charlie', age: 25 };
console.log(Object.entries(obj1)); // [['name', 'Charlie'], ['age', 25]]

// Object.freeze() - prevents any modifications to an object. It makes the object immutable, but shallowly- nested objects are not frozen
const book = { title: 'JavaScript Basics' };
Object.freeze(book);
book.title = 'New Title'; // No effect
console.log(book.title); // JavaScript Basics
book.author = 'John';  // Cannot add new property
console.log(book.author);  // undefined

// Object.getOwnPropertyDescriptor()
const person1 = { name: 'Bob' };
console.log(Object.getOwnPropertyDescriptor(person1, 'name')); // { value: 'Bob', writable: true, enumerable: true, configurable: true }

// Object.getOwnPropertyNames()
const car1 = { model: 'Ford', year: 2020 };
console.log(Object.getOwnPropertyNames(car1)); // ['model', 'year']

// Object.getOwnPropertySymbols()
const symbol1 = Symbol('id');
const obj2 = { [symbol1]: 123 };
console.log(Object.getOwnPropertySymbols(obj2)); // [Symbol(id)]

// Object.getPrototypeOf()
const prototypeObj = { greet: () => console.log('Hi!') };
const obj3 = Object.create(prototypeObj);
console.log(Object.getPrototypeOf(obj3) === prototypeObj); // true

// Object.is()
console.log(Object.is(25, 25)); // true
console.log(Object.is(NaN, NaN)); // true

// Object.isExtensible()
const obj4 = {};
console.log(Object.isExtensible(obj4)); // true
Object.preventExtensions(obj4);
console.log(Object.isExtensible(obj4)); // false

// Object.isFrozen()
const obj5 = { name: 'Frozen' };
Object.freeze(obj5);
console.log(Object.isFrozen(obj5)); // true

// Object.isSealed()
const obj6 = { title: 'Sealed' };
Object.seal(obj6);
console.log(Object.isSealed(obj6)); // true

// Object.preventExtensions()
const obj8 = { prop: 'value' };
Object.preventExtensions(obj8);
console.log(Object.isExtensible(obj8)); // false

// Object.seal()
const obj9 = { id: 1 };
Object.seal(obj9);
obj9.newProp = 'New'; // Won't be added
console.log(obj9); // { id: 1 }

// Object.setPrototypeOf()
const animalProto = { eat: () => console.log('Eating') };
const animalObj = { species: 'Dog' };
Object.setPrototypeOf(animalObj, animalProto);
animalObj.eat(); // Eating
