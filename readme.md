Light Bikes
============
Inspired by [Tron Legacy](https://en.wikipedia.org/wiki/Tron:_Legacy)

This is a game of lightbikes for the arduino with both single player and local multiplayer modes. Featuring adjustable colours and several A.I. to play against.
## Running instructions

- Setup hardware as specified
- Navigate to src/drivers/joystick_user.cpp, set the boolean values on line 45 and 49. These should be true if you are using the old style joystick, and false if you are using the new style joystick. Failure to do this will result in flipped controls
- navigate to the src folder
- `make upload`

### Hardware specifications
Part List:
- Arduino Mega2560 Board
- Adafruit ILI9341 Breakout (the touchscreen display + SD)
- 2x JoyStick Module


Wiring Instructions:

| Adafruit ILI9341 Pin | Arduino Pin |
|----------------------|-------------|
| GND                  | GND         |
| Vin                  | 5V          |
| CLK                  | 52          |
| MISO                 | 50          |
| MOSI                 | 51          |
| CS                   | 10          |
| D/C                  | 9           |
| Y+                   | A2          |
| X+                   | 4           |
| Y-                   | 5           |
| X-                   | A3          |
| CCS                  | 6           |


|Joystick1  |   Arduino |
|-----------------------|
|GND        |    GND    |
|HORZ       |    A0     |
|VERT       |    A1     |
|5V         |    5V     |

|Joystick2  |   Arduino |
|-----------------------|
|GND        |    GND    |
|HORZ       |    A4     |
|VERT       |    A5     |
|5V         |    5V     |

## A.I. in the game
Currently 4 A.I. listed in terms of difficulty, easiest is at top
- staying_alive_ai
- stalker_ai
- runner_ai
- possession_ai

This is according to my opinion after playing them

### Survivor (staying_alive_ai)
This A.I. simply looks one move ahead in each direction, then chooses one that won't immediately kill it.
It has perfect reflexes, but it is quite easy to trap giving it no choice but to hit a wall. The staying alive algorithm
is useful in implementing later A.I.'s

### Hunter (stalker_ai)
This A.I. charges head first at the other bike. But, it will not run into a wall.
Since the computer has perfect reflexes, the idea was to force the player to make a mistake by getting in their face.
This results in quite a lot of draws as it will choose to collide head on to the player rather then trap it.

### Coward (runner_ai)
Similar to the Hunter A.I. except it maximizes distance rather then minimizes it. This works a little better in my experience,
as the Hunter was quite easy to trap, this one squirms away like a slippery fish increasing it's survivability.
### Keeper (possession_ai)
This guy tries to maximize the space on the board that it 'possesses'. Possession is calculated as the amount of space it can get to before it's opponent.
It checks each possible move of his to see which would result in the most space it possesses relative to the opponent after it's move. This is done using a
modified [flood fill algorithm](https://en.wikipedia.org/wiki/Flood_fill) with a queue. Instead of starting with a single point, both this entity and the opponent are
added to the queue initially, then since it doesn't paint over non empty squares by keeping track of how much of each colour is painted, you have the relative possessions.
Then it's a simple matter to choose the direction with the most possession.

A.I. stratagy articles:
- https://web.stanford.edu/~jbboin/doc/ai_lightcycle.pdf
- http://www.sifflez.org/misc/tronbot/index.html
- https://www.a1k0n.net/2010/03/04/google-ai-postmortem.html


## Things to do
- Refactor, this project is fairly nicely organized, but it could be improved. Code reuse between the drivers is fairly minimal, and could definitely be improved upon.
As well, we have a hierarchical code structure, but our makefile doesn't really account for that, and it should. So figuring that out would be nice.
- Improve the GUI there are a some things we could do to make it work nicer. Like have a play again with same drivers button, or have a best of X games setting.
- Improve the A.I., our good A.I. is slow, and it would be nicer if it was faster. Or come up with a different algorithm that runs faster, but still plays smart
