#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT 30
#define WIDTH 100

#ifdef _WIN32
#include <windows.h>
#define SLEEP(t) Sleep(t * 1000)
#define CLEAR_SCREEN() system("cls")
#else
#include <unistd.h>
#define SLEEP(t) sleep(t)
#define CLEAR_SCREEN() system("clear")
#endif

int make_screen_array(char *screen_buffer) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            strcat(screen_buffer, " ");
        }
        if (y < HEIGHT - 1) {
            strcat(screen_buffer, "\n");
        }
    }

    return 0;
}

int draw_symbol(int ball_x, int ball_y, char *screen_buffer, char symbol) {
    if (ball_x < 0 || ball_x > WIDTH || ball_y < 0 || ball_y > HEIGHT) {
        return 1;
    }

    int location = ball_y * (WIDTH + 1) + ball_x;
    screen_buffer[location] = symbol;

    printf("\x1b[H");
    printf("%s", screen_buffer);
    fflush(stdout);

    return 0;
}


int main(int argc, char *argv[]) {
    printf("\x1b[8;%d;%dt", HEIGHT + 1, WIDTH + 2);
    printf("\x1b[?25l");
    CLEAR_SCREEN();

    char *screen_buffer = malloc((WIDTH + 1) * HEIGHT + 1);
    make_screen_array(screen_buffer);

    if (argv[1] && argv[2] && argv[3]) {
        int x = atoi(argv[1]);
        int y = atoi(argv[2]);
        char symbol = argv[3][0];
        draw_symbol(x, y, screen_buffer, symbol);
    } else {
        draw_symbol(8, 16, screen_buffer, 'x');
    }

    SLEEP(5);
    CLEAR_SCREEN();

    return 0;
}