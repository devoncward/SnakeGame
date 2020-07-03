#include "Display.h"

#include <stdio.h>

int Display_emptyScreen(char *display) {
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; ++i) {
        display[i] = '.';
    }

    return 1;
}

int Display_drawSnake(char *display) {
    // Enclosing top of grid border
    for (int i = 0; i < DISPLAY_WIDTH + 2; ++i) {
        printf("-");
    }

    //Spacing
    printf("\n");

    //The Grid Row
    for (int row = 0; row < DISPLAY_HEIGHT; ++row) {
        // For vertical grid enclosure
        printf("|");

        //The grid row itself
        for (int column = 0; column < DISPLAY_HEIGHT; ++column) {
            printf("%c", display[(DISPLAY_WIDTH * row) + column]);
        }

        // For vertigcal grid enclosure
        printf("|\n");
    }

    // Enclosing bottom of grid border
    for (int i = 0; i < DISPLAY_WIDTH + 2; ++i) {
        printf("-");
    }


    //Spacing
    printf("\n");

    return 1;
}