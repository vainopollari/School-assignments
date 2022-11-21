//Constants and variables
const button = document.getElementById('roll-button');
dices = ['ones', 'twos', 'threes', 'fours', 'fives', 'sixes'];
templates = ['template1', 'template2', 'template3', 'template4', 'template5', 'template6'];

// Add event listener to click
button.addEventListener('click', rollDice);

// Add event listener to custom event
document.addEventListener('rollDice', function(event){
    var value = event.detail.value;
    var dice = document.getElementById(dices[value - 1]);
    var span = document.getElementById('totals').querySelector('span');
    // Add each dice roll to total rolls
    var amount = parseInt(span.textContent, 10);
    span.textContent = amount + 1; 
    // Add to total rolls of each eye count
    if (dice.querySelector('p').textContent === '-'){
        dice.querySelector('p').textContent =  1;
    } 
    else {
        dice.querySelector('p').textContent++; 
    }
    // Update dice number after each click-event
    button.innerHTML = document.getElementById(templates[value - 1]).innerHTML;

});