#include "Control.h"
#include <cstdio>

bool stateMachineActive;

static enum ControlState {
    init_st,
    move_snake_st,
    check_snake_st,
    wait_for_input_st,
    game_over_st,
} currentState;

void Control_init() {
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
        currentState = move_snake_st;
        break;
    case move_snake_st:
        currentState = check_snake_st;
        break;
    case check_snake_st:
        // if Control_detectWallCollision() or Control_detectTailCollision()
        // true:
        currentState = game_over_st;
        break;
        // else
        currentState = wait_for_input_st;
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
    case move_snake_st:
        // get the user's input here to make the move, and calculate and execute
        // the move
        break;
    case check_snake_st:
        break;
    case wait_for_input_st:
        break;
    case game_over_st:
        stateMachineActive = false;
        break;
    }
}

bool Control_getStatusOfControlStateMachine() {
    return stateMachineActive;
}