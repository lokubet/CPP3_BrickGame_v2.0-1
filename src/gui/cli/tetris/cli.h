#ifndef CLI_H
#define CLI_H

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../../brick_game/tetris/tetris.h"  // Adjust the path based on your directory structure

// Constants for the UI dimensions
#define CLI_WIDTH 35   // Width of the terminal UI
#define CLI_HEIGHT 25  // Height of the terminal UI
#define PLAYFIELD_WIDTH 10
#define PLAYFIELD_HEIGHT 20

// Colors used in the UI
#define COLOR_PAIR_PIECE 1
#define COLOR_PAIR_BORDER 2
#define COLOR_PAIR_TEXT 3

// Function Prototypes
void init_cli();

void draw_start_screen();

void draw_game(TetrisGame *game, WINDOW *win);

void close_cli();

void draw_playfield(TetrisGame *game, WINDOW *win);

void draw_sidebar(TetrisGame *game);

void draw_pause_screen();

void draw_game_over_screen();

long long current_time_ms();

char handle_input(TetrisGame *game);

#endif  // CLI_H