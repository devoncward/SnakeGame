#include <stdio.h>
#include "Display.h"

//Will also need to create state machine here as example

//Note for Derek: use printf instead of cout, I like it better, and it offers more control in printing to the console

int main() {
    int foo = Display_drawSnake();
    printf("If this prints a 1, then my display.h function worked: %d\n", foo);
    return 0;
}