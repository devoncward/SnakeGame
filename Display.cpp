#include "Display.h"
#include <stdio.h>

static int display[DISPLAY_HEIGHT][DISPLAY_WIDTH];

int Display_clearArena() {
    for (int row = 0; row < DISPLAY_HEIGHT; ++row) {
        for (int column = 0; column < DISPLAY_WIDTH; ++column) {
            if (column == 0 || column == DISPLAY_WIDTH - 1 || row == 0 ||
                row == DISPLAY_HEIGHT - 1) {
                display[row][column] = '#';
            } else {
                display[row][column] = ' ';
            }
        }
    }

    return 1;
}

int Display_drawScreen() {
    for (int row = 0; row < DISPLAY_HEIGHT; ++row) {
        for (int column = 0; column < DISPLAY_WIDTH; ++column) {
            printf("%c", display[row][column]);
        }
        printf("\n");
    }

    return 1;
}

int Display_drawSnakeSection(int x, int y, int section) {
    if (section == 0) {
        // we're drawing the head
        display[x][y] = '0';
    } else {
        display[x][y] = 'x';
    }

    return 1;
}