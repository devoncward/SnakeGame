#include <stdio.h>
#include "Display.h"

int main() {
    int foo = Display_drawSnake();
    printf("If this prints a 1, then my display.h function worked: %d\n", foo);
    return 0;
}