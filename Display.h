#ifndef DISPLAY_H
#define DISPLAY_H

// Character lengths in the console, might need to change them later
#define DISPLAY_WIDTH 30
#define DISPLAY_HEIGHT 15

// To avoid "magic nukbers" later on in Display_resetDisplay() &
// Display_drawSnake()
/*
|-----------------------|
|         Width         |
|                       |
|                 Height|
|                       |
|                       |
|-----------------------|
*/

int Display_clearArena();

// Called to draw a function on the board. Draws the head, and all tail segments
// in the correct positions. Returns a 0 if an error was detected, 1 if
// successfully drawn
int Display_drawSnakeSection(int x, int y, int section);

// Called to draw the arena on the board. Returns a 0 if an error was detected,
// 1 if successfully drawn
int Display_drawScreen();

// Called to draw one new food item on the board. Returns a 0 if an error was
// detected, 1 if successfully drawn
int Display_drawFood();

// Called to remove current food item on the board. Returns a 0 if an error was
// detected, 1 if successfully drawn
int Display_clearFood();

// Called to draw the end game screen after we lose.
// Should also display the total score that we reached
int Display_drawEndGameScreen();

#endif