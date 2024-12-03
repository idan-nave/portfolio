    // Create a javascript file that connects to a html file
// In the html create an an input and an empty img element
// Based on the user input into the input tag display an img of a pokemon
// (To fetch the pokemon imgs use https://pokeapi.co/)
// For example:

const cont = document.getElementById('main_cont');
const ddl = document.getElementById('ddl');
const img = document.getElementById('img');

async function loadPage() {
    try {
        //fetch placeholder
        const ph_data = await fetch('https://jsonplaceholder.typicode.com/photos/1');
        const ph_jsonData = await ph_data.json();
        img.src = ph_jsonData.url;
        //fetch pokemon names list
        const poke_data = await fetch('https://pokeapi.co/api/v2/pokemon/');
        const poke_jsonData = await poke_data.json();
        const poke_names = poke_jsonData.results.map((element) => element.name);
        //fill dll
        poke_names.forEach((pokemon) => {
            const option = document.createElement('option'); 
            option.value = pokemon; // Set the value
            option.textContent = pokemon; // Set the displayed text
            ddl.appendChild(option); // Append the option to the dropdown
        });


    } catch (err) {
        console.log(err);
    }
}

async function fetchPokemon(selected) {
    try {
        const poke_data = await fetch('https://pokeapi.co/api/v2/pokemon/'+selected);
        const poke_jsonData = await poke_data.json();
        
        img.src=poke_jsonData.sprites.front_default;

    } catch (err) {
        console.log(err);
    }
}

loadPage();
// Add a keydown event listener to the input field
ddl.addEventListener('change', (event) => {
    fetchPokemon(ddl.value); // Run fetch logic when Enter is pressed
});

// Add a keydown event listener to the input field
// ddl.addEventListener('keydown', (event) => {
//     if (event.key === 'Enter') {
//         fetchPokemon(ddl.value); // Run fetch logic when Enter is pressed
//     }
// });