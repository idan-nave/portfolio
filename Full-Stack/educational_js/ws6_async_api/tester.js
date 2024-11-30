async function loadPage() {
    try {
        //fetch placeholder
        const ph_data = await fetch('https://jsonplaceholder.typicode.com/photos/1');
        const ph_jsonData = await ph_data.json();
        // img.src = ph_jsonData.url;
        //fetch pokemon names list
        const poke_data = await fetch('https://pokeapi.co/api/v2/pokemon/');
        const poke_jsonData = await poke_data.json();
        const poke_names = poke_jsonData.results.map((element) => element.name);
        console.log(poke_names);

    } catch (err) {
        console.log(err);
    }
}
loadPage();
