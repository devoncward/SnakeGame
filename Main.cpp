#include <stdio.h>
#include "Display.h"
#include "Control.h"
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

static enum MainState {
    init_st,
    waiting_for_key_press_st,
    perform_game_st,
    end_game_st
} currentState;

static char snakeName[MAX_SNAKE_NAME_SIZE] = DEFAULT_SNAKE_NAME;

//This function inits the variables we will use in the state machine
static void init() {
    currentState = init_st;
    gameActive = true;
    printf("We are initializing the state machine\n");
}

// Displays changes of states in the state machine
static void debugStateMachine() {
    static enum MainState previousState;
    if(previousState != currentState) {
        previousState = currentState;
        switch(currentState) {
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
    debugStateMachine();

    //Transitions of the state machine
    switch(currentState) {
        case init_st:
            currentState = waiting_for_key_press_st;
            break;
        case waiting_for_key_press_st:
            //Receive basic input for game
            printf("Welcome to the snake game! Please enter the name of the snake you will be competing with\n");
            scanf("%s", snakeName);
            printf("\nYou have chosen %s, good luck!\n\n", snakeName);
            currentState = perform_game_st;
            break;
        case perform_game_st:
            //if game is over, transition to game over state
            if(!gameActive) {
                printf("Good try!\n");
                currentState = end_game_st;
            } else { //Keep on playing the game
                currentState = perform_game_st;
            }
            break;
        case end_game_st:
            currentState = end_game_st;
            break;
    }

    //Actions of the state machine
    switch(currentState) {
        case init_st:
            //Should not do anything here, we instead call the init() function
            break;
        case waiting_for_key_press_st:
            break;
        case perform_game_st:
            //Perform the tick function of the Control State Machine
            //Control_activateControlStateMachine(true);
            break;
        case end_game_st:
            gameActive = false; // Not really needed
            break;
    }
}

int main() {
    //Init the state machine
    init();

    //Begin the game
    while(gameActive) {
        // Tick function of Control State
        tickFunction();
        usleep(MAIN_TICK_RATE); //Accepts microseconds
    }
    return 0;
}