#include "Display.h"
#include <stdio.h>

static int display[DISPLAY_WIDTH][DISPLAY_HEIGHT];

int Display_initializeScreen() {
    for (int row = 0; row < DISPLAY_HEIGHT; ++row) {
        for (int column = 0; column < DISPLAY_WIDTH; ++column) {
            if (column == 0 || column == DISPLAY_WIDTH - 1 || row == 0 ||
                row == DISPLAY_HEIGHT - 1) {
                display[row][column] = '&';
            } else {
                display[row][column] = '.';
            }
        }
    }

    return 1;
}

int Display_drawArena() {
    for (int row = 0; row < DISPLAY_HEIGHT; ++row) {
        for (int column = 0; column < DISPLAY_WIDTH; ++column) {
            printf("%c", display[row][column]);
        }
        printf("\n");
    }

    return 1;
}

int Display_drawSnake() {
    printf("Drawing snake...\n");
    Display_drawArena();

    return 1;
}