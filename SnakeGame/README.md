# SnakeGame

Classic old school SnakeGame on console. Game ready to download, compile and run.<br>

## Structure

The game has the following objects:<br>

**Controller**: reads "w", "a", "s", "d" input from keyboard to direct snake's movement and "x" to quit the game;<br>
**Snake**: the main character, manages its own movement and keeps track of its length and tail component locations for collision checks;<br>
**Board**: visual representation of a 20x20 array of chars, where the snake's head is "O" and the tail components are "o", food is "$";<br>
**Food**: food is spawned randomly, making sure not to be spawned on the snake's body; <br>
**CollisionManager**: checks for all collision situations: when the head collides with the tail, when the head collides with food, when the food might get spawned on the snake's body.<br>
**Gamestate**: determines the state of the game.<br>

## How the game is rendered on console

Each time the board is printed to console, the cursor of the console is moved to the top left corner so that each next print overlaps the current one in order to avoid printing a new board at each loop iteration.<br>In order to slow the speed of execution down inside the loop, so that the game might be playable, the thread is sent to sleep for 150 ms at each iteration of the loop.<br>
In this way we can fake a continuous movement of the snake on a stationary board on console and make it be reactive to input in real-time.<br>

## Movement

Snake's movement is continuous towards the direction it has been given by input. Its head and tail coordinates are incremented or decremented at each iteration of the loop.<br>

## How the snake's body is composed

The Snake's body is made out of a head and many tail components. The head directs movement and is checked against collisions with food and its tail. It occupies one position in the board array.<br>
The tail is made of many tail components, each of which occupies one position in the array like the head, and follows the head in its movement.<br>
Each time the snake eats food, a new tail component is added to the body.<br>

## How the snake knows when it bites itself

The snake caches the coordinates of its tail components in a vector container that is updated at each iteration, as the coordinates change continuously when the snake moves. In this way we can determine when it collides with its own body.<br>

## Game rules

The game represents the classical snake game. The only failure condition is when the snake collides with itself. A hypotethical win is attributed by the Gamestate if it reaches length 400, which we believe is impossible!<br>


