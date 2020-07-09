#include "Control.h"
#include "Display.h"
#include <cstdio>

#define X_VELOCITY 1
#define Y_VELOCITY 1

location snakeSections[MAX_SNAKE_SIZE];
int snakeSize;

bool stateMachineActive;

static enum SnakeDirection {
    up,
    down,
    left,
    right,
} movementDirection;

static enum ControlState {
    init_st,
    init_snake_st,
    move_snake_st,
    check_snake_st,
    wait_for_input_st,
    game_over_st,
} currentState;

void Control_init() {
    snakeSize         = DEFAULT_SNAKE_SIZE;
    movementDirection = right;

    // Assign the snake it's initial positions
    for (int initialSnakeSection = 0; initialSnakeSection < snakeSize;
         ++initialSnakeSection) {

        // Default snake sections get assigned from the top right corner
        // downward in such a way that the snake faces downward when the game
        // starts
        snakeSections[initialSnakeSection].x = snakeSize - initialSnakeSection;
        snakeSections[initialSnakeSection].y = 1;
        printf("(%d, %d)\n", snakeSections[initialSnakeSection].x,
               snakeSections[initialSnakeSection].y);
    }

    stateMachineActive = true;
    currentState       = init_st;
}

void Control_debugStateMachine() {
    static bool firstPass = true;
    static enum ControlState previousState;

    if (currentState != previousState || firstPass) {
        firstPass     = false;
        previousState = currentState;
        switch (currentState) {
        case init_st:
            printf("\tEntering Control Init State\n");
            break;
        case init_snake_st:
            printf("\tEntering Init Snake State\n");
            break;
        case move_snake_st:
            printf("\tEntering Control Move Snake St\n");
            break;
        case check_snake_st:
            printf("\tEntering Control Check Snake St\n");
            break;
        case wait_for_input_st:
            printf("\tEntering Control Wait For Input St\n");
            break;
        case game_over_st:
            printf("\tEntering Control Game Over St\n");
            break;
        }
    }
}

void Control_tickFunction() {
    // Transitions of the state machine
    switch (currentState) {
    case init_st:
        currentState = init_snake_st;
        break;
    case init_snake_st:
        currentState = move_snake_st;
        break;
    case move_snake_st:
        currentState = check_snake_st;
        break;
    case check_snake_st:
        if (Control_detectWallCollision() || Control_detectTailCollision()) {
            currentState = game_over_st;
        } else {
            Control_updateScreen();
            currentState = wait_for_input_st;
        }
        break;
    case wait_for_input_st:
        currentState = move_snake_st;
        break;
    case game_over_st:
        break;
    }

    Control_debugStateMachine();

    // Actions of the state machine
    switch (currentState) {
    case init_st:
        break;
    case init_snake_st:
        break;
    case move_snake_st:
        Control_updateSnake();
        break;
    case check_snake_st:
        break;
    case wait_for_input_st:
        // wait for the user's input...
        break;
    case game_over_st:
        stateMachineActive = false;
        break;
    }
}

bool Control_getStatusOfControlStateMachine() {
    return stateMachineActive;
}

bool Control_detectWallCollision() {
    for (int section = 0; section < snakeSize; ++section) {
        if (snakeSections[section].x == 0 ||
            snakeSections[section].x == DISPLAY_HEIGHT - 1 ||
            snakeSections[section].y == 0 ||
            snakeSections[section].y == DISPLAY_WIDTH - 1)
            return true;
    }
    return false;
}

bool Control_detectTailCollision() {
    return false;
}

void Control_updateSnake() {
    for (int section = snakeSize; section > 1; --section) {
        snakeSections[section - 1].x = snakeSections[section - 2].x;
        snakeSections[section - 1].y = snakeSections[section - 2].y;
    }

    switch (movementDirection) {
    case up:
        snakeSections[0].x -= 1;
        break;
    case down:
        snakeSections[0].x += 1;
        break;
    case left:
        snakeSections[0].y -= 1;
        break;
    case right:
        snakeSections[0].y += 1;
    }
}

void Control_updateScreen() {
    Display_clearArena();
    for (int section = 0; section < snakeSize; ++section) {
        Display_drawSnakeSection(snakeSections[section].x,
                                 snakeSections[section].y, section);
    }
    Display_drawScreen();
}