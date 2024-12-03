// Create an html page with a button and a list, when clicking on the button, perform a fetch request to the following API - 
// https://jsonplaceholder.typicode.com/
// And display 5, random emails from the API in a list, on the html page.
const fetchBtn = document.getElementById('btn');
const emailList = document.getElementById('list');

fetchBtn.addEventListener('click', () => {
    // fetch
    emailList.innerHTML = 'Emails wiill display here:';
    let fetchedEmails = emailsFetcher();
    console.log(fetchedEmails);// pricessed

    // show in list
    fetchedEmails.forEach(email => {
        const listItem = document.createElement('li');
        listItem.textContent = email;
        emailList.appendChild(listItem);
    });
});

async function emailsFetcher() {
    try {
        const response = await fetch('https://jsonplaceholder.typicode.com/users');

        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const data = await response.json();

        // console.log(data);// all of json 

        const emails = data
            .sort(() => 0.5 - Math.random()) // randomize
            .slice(0, 5) // minimize to 5 emails
            .map(user => user.email); // select

        // console.log(emails);// pricessed

        return emails;
    } catch (error) {
        console.error('Error fetching data:', error);
    }
}