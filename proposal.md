Jacob Reckhard (1497646) and Jarrett Yu (1493740)

Light Bikes
============
Inspired by [Tron Legacy](https://en.wikipedia.org/wiki/Tron:_Legacy)

## Parts of the project

### Titlescreen

Will have a select for whether to start, 2 player mode, or 1 player + A.I.
In the background is 2 A.I. Players playing

### The Battlefield
Bikes leave a trail of lights.
If a bike runs into a trail it dies.
The goal is to be the last one left.
Don't run into trails.
Constant time between frame ticks

#### Player
Player control is done by using the joystick

Can choose color at beginning of game

#### A.I. ideas
For the A.I. we would like to implement several different stratagies,
these are some of our initial thoughts on A.I. strategies and all likely will not make it into the final implementation.


##### Simple
Goes straight has a 10 percent chance to randomly turn left or right.
If would drive into a tile that it can avoid, it will.

##### Finite State
Finite state machine:
states would be early game, middle game, end game, attacking, defending
each would have it's own routine where behavior is defined differently
eg)
    starts in early game, board is relatively free, once a certain amount of lines are placed, switch to middle game.
    If in an attacking position switch to attacking, if forced into a defensive position, switch to defense.
    Once the player and enemy are in separate boxes switch to endgame.

##### Neural Network
Input nodes would be the state of every cell on the board
Output nodes would be two representing a Binary Encoded decimal corresponding to the move choice, left, right, or straight
Trained with a genetic algorithm, playing against itself, maybe even against other A.I.

##### Deep Neural Network
Same as above but with 2 layers of hidden neurons, requires more training

##### Min-Max with Alpha–beta pruning
Looks ahead a few ticks trying all possible combinations of moves to see which is the best condition.
Each cycle both players could make 3 different moves, turn left, turn right, move straight.
The best conditions would be maximizing it's space on a [Voronoi Diagram](https://en.wikipedia.org/wiki/Voronoi_diagram).
Voronoi Diagram would be calculated using Dijkstra's or A* algorithm.
If too slow with all the searching on every point, use a Monte Carlo approximation.

## Milestone goals
- [x] Have a working two player light bike game
- [x] Create a basic title screen
- [x] Create a basic A.I. player for 1 player mode
- [x] Create player color selection system
- [ ] Create a title screen with A.I. players competing
- [x] Create a more advanced A.I. (new A.I. or variable difficulty for basic A.I.)
- [x] Adjustable difficulties for the A.I.
