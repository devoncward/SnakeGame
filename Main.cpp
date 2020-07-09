#include "Control.h"
#include "Display.h"
#include <stdio.h>
#include <unistd.h>

/*
Look into:
    sscanf
    clock rate in state machine
    clearing console
*/

#define MAIN_TICK_RATE 1E5 // 1/10 sec in usec

#define MAX_SNAKE_NAME_SIZE 50
#define DEFAULT_SNAKE_NAME "Snakey"

static bool gameActive;
static char snakeName[MAX_SNAKE_NAME_SIZE];

static enum MainState {
    init_st,
    waiting_for_key_press_st,
    perform_game_st,
    end_game_st
} currentState;

// This function inits the variables we will use in the state machine
static void init() {
    currentState = init_st;
    gameActive   = true;
    Display_initializeScreen();
    printf("We are initializing the state machine\n");
}

// Displays changes of states in the state machine
static void debugStateMachine() {
    static bool firstPass = true;
    static enum MainState previousState;
    // on first pass, previousState is undefined, so could cause undefined
    // behavior. To prevent: firstPass is true upon first pass to guarantee
    // first execution here
    if (previousState != currentState || firstPass) {
        firstPass     = false;
        previousState = currentState;
        switch (currentState) {
        case init_st:
            printf("Entering Main Init State\n");
            break;
        case waiting_for_key_press_st:
            printf("Entering Main Waiting For Key Press State\n");
            break;
        case perform_game_st:
            printf("Entering Main Perform Game State\n");
            break;
        case end_game_st:
            printf("Entering Main End Game State\n");
            break;
        }
    }
}

// Called every tick, does transitions and actions of state machine
static void tickFunction() {

    // Transitions of the state machine
    switch (currentState) {
    case init_st:
        Control_init();
        currentState = waiting_for_key_press_st;
        break;
    case waiting_for_key_press_st:
        // Receive basic input for game
        printf("Welcome to the snake game! Please enter the name of the snake "
               "you will be competing with\n");
        scanf("%s", snakeName);
        printf("\nYou have chosen %s, good luck!\n\n", snakeName);
        currentState = perform_game_st;
        break;
    case perform_game_st:
        // if game is over, transition to game over state
        gameActive = Control_getStatusOfControlStateMachine();
        if (!gameActive) {
            printf("Good try!\n");
            currentState = end_game_st;
        } else { // Keep on playing the game
            currentState = perform_game_st;
        }
        break;
    case end_game_st:
        currentState = end_game_st;
        break;
    }

    // function moved here for more clarity upon "entering" a state. Placing
    // this function at the top of the tick function, certain values never get
    // printed by the debugStateMachine(), and sometimes debugStateMachine() is
    // a tick behind in printing out the actual value
    debugStateMachine();

    // Actions of the state machine
    switch (currentState) {
    case init_st:
        // Should not do anything here, we instead call the init() function
        break;
    case waiting_for_key_press_st:
        break;
    case perform_game_st:
        // Perform the tick function of the Control State Machine
        Control_tickFunction();
        break;
    case end_game_st:
        printf("Endgamestuff...\n");
        // Display_drawEndGameScreen();
        break;
    }
}

int main() {
    // Init the state machine
    init();

    // Begin the game
    while (gameActive) {
        // Tick function of Control State
        tickFunction();
        usleep(MAIN_TICK_RATE); // Accepts microseconds
    }
    return 0;
}