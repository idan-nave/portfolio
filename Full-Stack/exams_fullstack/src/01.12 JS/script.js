// Create an HTML page with an input field, a button, and a result display area.
//When the button is clicked, a JavaScript function should receive a string as a parameter from the input field. The function should then find the longest word in the string and display it in the result area.

// Example: Given input: 'The quick brown fox jumps over the lazy dog'
// If the button is clicked, the result should display 'jumps' as it's the longest word in the input string.
document.addEventListener('DOMContentLoaded', () => {

    const input = document.getElementById('input');
    const find_btn = document.getElementById('find_btn');
    const result = document.getElementById('result');

    // Button event
    find_btn.addEventListener('click', () => {
        if (input) {
            result.value = findLargestWord(input.value);
        }
        else {
            result.value = 'missing input';
        }
    });

    function findLargestWord(inputText) {
        let words = inputText.split(' ');
        let max = 0;
        let largest = '';

        words.forEach(word => {
            let wordLength = word.length;
            if (wordLength > max) {
                largest = word;
                max = wordLength;
            }
        });

        return largest; 
    }


});
