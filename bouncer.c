#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 32
#define HEIGHT 32
#define FPS 30

static char FRAMEBUFFER[WIDTH * HEIGHT * 2];

void printLabel() {
    printf("=================================================\n");
    printf("====================!Bouncer!====================\n");
    printf("=================================================\n");
}

void printFrameBuffer() {
    printf("\033[0;0H"); // This is the ansi escape code for moving the cursor to 0, 0
    //Print the label at the top of the screen
    printLabel();
    for (int i = 0; i < HEIGHT; i ++) {
        for (int j = 0; j < WIDTH * 2; j ++) {
            printf("%c", FRAMEBUFFER[i * WIDTH * 2 + j]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y, char brightness) {
    if (x > 0 && x < WIDTH) {
        if (y > 0 && y < HEIGHT) {
            FRAMEBUFFER[y * WIDTH * 2 + x * 2] = brightness;
            FRAMEBUFFER[y * WIDTH * 2 + x * 2 + 1] = brightness;
        }
    }
}

void fillRect(int x, int y, int w, int h, char brightness) {
    for (int _x = x; _x < x + w; _x ++) {
        for (int _y = y; _y < y + h; _y ++) {
            setPixel(_x, _y, brightness);
        }
    }
}

//Unique game related constants
#define GRAVITY 2
#define DAMPER -0.8f

int main() {
    //This uses the ansi escape code to clear the screen
    printf("\x1b[2J");
    //Defining variables
    const float dt = 1.0f/FPS;
    float x = 0.0f, y = 0.0f;
    float xv = 9.0f, yv = 0.0f;

    int shouldQuit = 0;
    while (!shouldQuit) {
        //Logic
        yv += GRAVITY;
        y += yv * dt;
        x += xv * dt;

        if (y + 3.0f >= HEIGHT) {
            y = HEIGHT - 3.0f;
            yv = yv * DAMPER;
        }
        if (x > WIDTH) {
            x = 0.0f;
            y = 0.0f;
            xv = 9.0f;
            yv = 0.0f;
        }
       
        //Drawing
        memset(FRAMEBUFFER, '.', WIDTH * HEIGHT * 2);
        fillRect((int)x, (int)y, 3, 3, '#');
        printFrameBuffer();
        usleep(1000000.0f/FPS);
    }
    printf("\x1b[2J"); // An ansi escape code that clears the screen before returning control to the terminal
    return 0;
}
