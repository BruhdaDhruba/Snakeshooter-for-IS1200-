#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pic32mx.h> 
#include "Snakeshooter.h"

bool gun_intact = true;
//bool new_level = true;
int buttons;
//int level = 0;
snakesalive = 4;
int bulletCount = 0;
int speed = 1000;

int abs(int val) {
    return val < 0 ? -val : val;
}

void destroy_dart() {
    dart.shot = false; // Reset shot flag
    // Regenerate dart at the beginning of the gun
    int i;
    for (i = 0; i < dart.length; i++) {
        dart.x[i] = gun.x[i]; // Set dart x-coordinate to gun's x-coordinate
        dart.y[i] = gun.y[0]; // Set dart y-coordinate to gun's y-coordinate
    }
}

void game(){
    int i;
    gun_move();
    dart_move();
    snake_move();

    for(i = 0; i < 4; i++){
        bool dart_below_snake_y = dart.y[0] >= snakes[i].y;
        bool dart_above_snake_last_y = dart.y[0] <= snakes[i].y + snakes[i].width;
        bool y_hit = dart_below_snake_y && dart_above_snake_last_y;

        if(dart.x[dart.length - 1] >= snakes[i].x[0] && y_hit){
            damageSnake(i);
            destroy_dart();
            
            if(snakes[i].length == 0){
                score++;
            }
        }
    }

    gen_gun();
    gen_dart();
    
    gen_snake();

    for(i = 0; i < 4; i++){
    if(snakes[i].x[0] <= gun.x[2]){
        gameOver();
    }
    }

    /*#define TRISE PIC32_R (0xbf886100)
    TRISE = TRISE & ~0xff;   // Port E is used for the LED 
	//Set bits 0 through 7 to 0 (output) 
    PORTE = 0b00000000;
    TRISD = TRISD | 0x03F0;
    */

    if(score == 4){
        victory();
    }

    /*if(new_level){
        level++;
        next_level();
    }*/
    
    delay(speed);
}


void gun_move() {
    buttons = get_btns();
    if (buttons & 0b0010)
        gun.dir = 'U';
    else if (buttons & 0b0100)
        gun.dir = 'D';
    else
        gun.dir = 'N'; //no direction

    // Move each pixel of the gun down
    if (gun.dir == 'U') { //UP
        int i;
        for (i = 0; i < 3; i++) {
            if (gun.y[i] > 0) { // Check if not at the top boundary
                gun.y[i] -= 1;
            }
        }
    }

    if (gun.dir == 'D') { //DOWN
        int j;
        for (j = 0; j < 3; j++) {
            if (gun.y[j] < 31) { // Check if not at the bottom boundary
                gun.y[j] += 1;
            }
        }
    }

    // Move dart if it's not shot and gun is moved
    if (!dart.shot) {
        int i;
        for (i = 0; i < dart.length; i++) {
            if (gun.dir == 'U' && dart.y[i] > 0) { // Move dart up
                dart.y[i] -= 1;
            } else if (gun.dir == 'D' && dart.y[i] < 31) { // Move dart down
                dart.y[i] += 1;
            }
        }
    }

    int buttonPressed = 0;

    // Existing gun_move() code here...

    // Allow shooting only if bullet count is less than maximum limit (7)
    if ((buttons & 0b0001) && !buttonPressed && bulletCount < 7) {
        buttonPressed = 1;
        dart.shot = true;
    }

    // Reset buttonPressed flag if no longer pressed
    if (!(buttons & 0b0001)) {
        buttonPressed = 0;
    }

    
}


void snake_move(){
    int i, j;
    for (i = 0; i < 4; i++){
        if(snakes[i].alive){
            snakes[i].x[0] -= 1;
            for(j = snakes[i].length - 1; j > 0; j--){ //Ensures that the snake moves towards the gun i.e left
                snakes[i].x[j] = snakes[i].x[j - 1];
            }
        }
    }
}


void dart_move() {
    static int buttonPressed = 0; // Flag to track if the button has been pressed

    // Check if the button is pressed for the first time
    if ((buttons & 0b0001) && !buttonPressed) {
        buttonPressed = 1; // Set the flag to indicate that the button has been pressed
        dart.shot = true; // Dart is shot
    }

    // Move dart if it's shot
    if (dart.shot) {
        int i;
        for (i = 0; i < dart.length; i++) {
            if (dart.x[i] < 127) { // If dart is not at the end of the screen
                dart.x[i] += 10;    // Move dart two pixels at a time
            } else { // If dart reaches end of screen
                destroy_dart();
            }
        }
    }

    // Reset buttonPressed flag if no longer pressed
    if (!(buttons & 0b0001)) {
        buttonPressed = 0;
    }
}



void damageSnake(int snakenumber){
    snakesalive--;
    int i;
    int x, y;
    
    for(i = 0; i < 3; i++){
        x = snakes[snakenumber].x[snakes[snakenumber].length - i - 1];
        y = snakes[snakenumber].y;
        display[y][x] = 0;
    }
    
    snakes[snakenumber].length -= 3;
    
    if (snakes[snakenumber].length <= 0) {
        snakes[snakenumber].alive = false;
        snakes[snakenumber].length = 0;  // Ensure the snake's length doesn't become negative
    }
}

void gen_gun(){
    int i;
    int x, y;
    for(i = 0; i < gun.length; i++){
        x = gun.x[i];
        y = gun.y[0];
        display[y][x] = 1;
    }
}

void gen_dart(){
    int i;
    int x, y;
    for(i = 0; i < dart.length; i++){
        x = dart.x[i];
        y = dart.y[0];
        display[y][x] = 1;
    }
}

void gen_snake(){
    int x_idx, y_idx, j;
    int x, y;

    for(j = 0; j < sizeof(SnakeRows) / sizeof(SnakeRows[0]); j++){
        Snake snake = snakes[j];

        for(x_idx = 0; x_idx < snake.length; x_idx++){
            x = snake.x[x_idx];

            for(y_idx = 0; y_idx < snake.width; y_idx++) {
                y = snake.y + y_idx;
                display[y][x] = 1;
            }
        }
    }
}


/*Written by Fredrik Lundström and Michell Dib 2021, modified by Turja Das 2024*/
void gameOver(){
    char score2[] = "X";
    score2[0] = score + '0'; //Here we make an integer to a string

    while(buttons != 0b1000){ //While BTN4 is not pressed we will display the score and a game over string.
        clear_display();
        display_string(1, "NICE! YOUR SCORE: ");
        display_string(2, score2);
        display_update();
        translateToImage();
	    //display_image(0, oled_display);
        buttons = get_btns();
    }
    main(); //If BTN4 is pressed we jump back to main and the game will then restart. 
}

/*Modified version of gameOver which was written by Fredrik Lundström and Michell Dib 2021*/
void victory(){
    while(buttons != 0b1000){ //While BTN4 is not pressed we will display the score and a game over string.
        clear_display();
        display_string(1, "VICTORY!");
        display_update();
        translateToImage();
	    //display_image(0, oled_display);
        buttons = get_btns();
    }
    main(); //If BTN4 is pressed we jump back to main and the game will then restart. 
}

int get_btns(void) {
	int btns = (PORTD >> 4) & 0x000E; 

    btns = ((PORTF >> 1) & 0x1) | btns;                              
    return btns;
}