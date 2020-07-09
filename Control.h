#ifndef CONTROL_H
#define CONTROL_H

#define DEFAULT_SNAKE_SIZE 3 // Does not include the tail

struct location {
    int x;
    int y;
};

// This is the score of the game, every time we eat one food, this increments
// int score;

// Init state function for control state machine
void Control_init();

// Debug function to display transitions for the state machine
void Control_debugStateMachine();

// Standard tick function for control state machine
void Control_tickFunction();

// Returns true if snake hits a wall, false otherwise
bool Control_detectWallCollision();

// Returns true if snake hits itself, false otherwise
bool Control_detectTailCollision();

// Activates the state machine by setting stateMachineStatus true or false
// through value input parameter
int Control_activateControlStateMachine(bool value);

// Returns the status of the Control state machine
bool Control_getStatusOfControlStateMachine();

// Returns a location of a random food within the bounds of the display
location Control_foodLocation();

#endif