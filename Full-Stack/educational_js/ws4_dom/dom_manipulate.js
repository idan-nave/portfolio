// const main = document.getElementById('main');
// main.innerHTML = 'world';

// main.style.color = 'blue'

// main.setAttribute('class', 'blue');

// const container = document.createElement('div');
// container.innerHTML = 'I am here'
// document.body.appendChild(container)
// main.appendChild(container)

// const button = document.getElementById('button');
// button.addEventListener('click', (e) => console.log(e.target.innerHTML));


//Question 4:
// Create a dropdown menu with three options: "Option 1", "Option
// 2", and "Option 3". Use JavaScript to add an event listener to
// the dropdown menu that logs the selected option to the
// console.

// const select = document.getElementById('select');
// select.addEventListener('change', (e) => {
//     console.log(e);
//     const selectElement = e.target;
//     const selectedOption = selectElement[selectElement.selectedIndex];
//     console.log(selectedOption.innerText);

// })

// Question 6 :

const input = document.getElementById('input');
const button = document.getElementById('button');
const list = document.getElementById('list');

button.addEventListener('click', () => {
    //get value of input
    const taskValue = input.value;
    //create new element with the value from input
    const newTask = document.createElement('li');
    newTask.innerHTML = taskValue;
    list.appendChild(newTask);
    //clear input after button click
    input.value = ''
})