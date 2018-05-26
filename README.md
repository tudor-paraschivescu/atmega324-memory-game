# RGB Memory Game

# Description
Electronic memory game designed for ATmega 324 microcontrollers with multiple single and multiplayer modes that will test the speed and coordination of the participants.

The game wants to be a slightly simplified version of [MiniWizard](https://www.vtechkids.com/assets/data/products/%7BB165F8D6-DD6C-4E06-8937-6B59C974892F%7D/manuals/Mini_Wizard.pdf) - the fun electronic game that helped kids learn in the '80s.

The usefulness of such a game exists even today, because the small ones can learn and have fun in the same time, while developing their competitive spirit. However, the game is not only for children, as it can represent a good way for adults to escape the stress, while teenagers can create drinking games with this device (it's just an idea, you didn't heard it from me).

# Hardware Description
The game has a RGB LED 3x3 matrix, which will light up and will form different patterns that must be followed by the players, and a gamepad with 4 buttons to interact with the game. Additionally, there is a button to switch from one game mode to another and a 2x16 LCD to display messages about the selected game, progress, winners and losers.

# Game modes

### MATCH ME (single-player)
**Objective**: Remember and repeat the lights
**Game rules**: One LED of the 4 sides (random selection) will light up. After that, the player must repeat the LED position by pressing the corresponding button. If pressed correctly, the game will tell us this on the LCD and on the LED matrix, then move to the next round where a new side will be added. This continues until the player fails or wins the game.
**Win**: To win the player must go through 10 rounds.

### HAMMERING HANDS (single-player)
**Objective**: Quickly press the button while the LED is turned on.
**Game rules**: One LED of the 4 sides (random selection) will light up, the player must immediately press (in under 300ms) the corresponding button. If he can press the button in time, then the game continues and a new light will appear and so on.
**Win**: To win the player must go through 10 rounds.

### GREEN HAMMERING HANDS (single-player)
**Objective**: Quickly press the green button while the corresponding LED is turned on.
**Game rules**: One LED of the 4 sides (random selection) will light up, the player must immediately press (in under 500ms) the corresponding button if the LED's color is green. If he can press the button in time, then the game continues and a new light will appear and so on. In the case of other color than green, the player does not have to press anything.
**Win**: To win the player must go through 10 rounds.

### CENTER SHOT (multiplayer)
Not (yet) implemented.

### BLUE CENTER SHOT (multiplayer)
**Objective**: Quickly press your button when there is a blue light in the middle.
**Game rules**: When the central LED lights up in blue, the player must immediately press his button. If other lights are lit, nothing must be pressed. If the central LED lights up with a color other than blue, nothing should be pressed. The player that presses first his button receives 1 point if the flashing light is blue, otherwise he loses 1 point. There will be 20 rounds and the starting score is 0.
**Win**: The player with the most points wins.
