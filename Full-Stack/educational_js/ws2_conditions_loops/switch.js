// program for a simple calculator
let result;
// take the operator input
const operator = either +, -, * or /;
// take the operand input
const number1 = 4
const number2 = 5
switch (operator) {
  case '+':
    result = number1 + number2;
    console.log(`${number1} + ${number2} =
${result}`);
    break;
  case '-':
    result = number1 - number2;
    console.log(`${number1} - ${number2} =
${result}`);
    break;
  case '*':
    result = number1 * number2;
    console.log(`${number1} * ${number2} =
${result}`);

    break;
  case '/':
    result = number1 / number2;
    console.log(`${number1} / ${number2} =
${result}`);
    break;
  default:
    console.log('Invalid operator');
    break;


// multiple case switch program
let fruit = 'apple';
switch(fruit) {
case 'apple':
case 'mango':
case 'pineapple':
console.log(`${fruit} is a fruit.`);
break;
default:
console.log(`${fruit} is not a fruit.`);
break;
}