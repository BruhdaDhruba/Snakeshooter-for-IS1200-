#include <stdbool.h>

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

void quicksleep(int cyc);

void display_debug( volatile int * const addr );

extern const uint8_t const font[128*8];
extern const uint8_t const icon[128];
extern char textbuffer[4][16];

uint8_t display[32][128]; //Human readable pixel position and activation
uint8_t oled_display[512]; //Computer readable pixel position and activation

void delay(int);
void enable_interrupt(void);



uint8_t gunX[32];
uint8_t gunY[32];

uint8_t dartX[128];
uint8_t dartY[32];

uint8_t snakeX[9];
uint8_t snakeY[9];

int score;
void gun_move();
void snake_move();
void dart_move();
void damageSnake();
void gen_gun();
void gen_dart();
void gen_snake();
void gameOver();
void victory();
int get_btns(void);
//void next_level();

int snakesalive;
int SnakeRows[4];


typedef struct Blowgun //Object blowgun
{
    uint8_t *y; 
    uint8_t *x;
    int length;
    char dir;
} Blowgun;

Blowgun gun;

typedef struct Dart {
    uint8_t *y; 
    uint8_t *x;
    int length;
    bool shot; // Flag to indicate if the dart has been shot
} Dart;

Dart dart;

typedef struct Snake //Object snake
{
    uint8_t y; 
    uint8_t x[16];
    int width;
    int length;
    bool alive;
} Snake;

Snake snakes[4];
