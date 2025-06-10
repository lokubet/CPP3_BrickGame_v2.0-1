#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

#define SCORE_FILE "./score.txt"  // Ensure it's in the current directory
#define NUM_PIECES 7

typedef struct {
  int x;
  int y;
} Point;

// Structure to represent a Tetris piece
typedef struct {
  Point positions[4];
  int type;
  int rotation;
} Piece;

typedef enum { MENU, PLAYING, PAUSED, GAME_OVER } GameState;

// Structure to represent the game state
typedef struct {
  GameState state;                       // Current state of the game
  int field[FIELD_HEIGHT][FIELD_WIDTH];  // Playing field matrix
  Piece current_piece;                   // The currently falling piece
  Piece next_piece;                      // The next piece to be spawned
  int score;
  int max_score;  // Maximum score recorded
  int level;      // Current level
} TetrisGame;

// Define the shapes of the Tetris pieces
static const Point PIECES[NUM_PIECES][4][4] = {
    // I_SHAPE
    {{{0, -1}, {0, 0}, {0, 1}, {0, 2}},
     {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
     {{0, -1}, {0, 0}, {0, 1}, {0, 2}},
     {{-1, 0}, {0, 0}, {1, 0}, {2, 0}}},
    // O_SHAPE
    {{{0, 0}, {0, 1}, {1, 0}, {1, 1}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}}},
    // T_SHAPE
    {{{0, -1}, {0, 0}, {0, 1}, {1, 0}},
     {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},
     {{0, -1}, {0, 0}, {0, 1}, {-1, 0}},
     {{-1, 0}, {0, 0}, {1, 0}, {0, -1}}},
    // S_SHAPE
    {{{0, -1}, {0, 0}, {1, 0}, {1, 1}},
     {{-1, 0}, {0, 0}, {0, 1}, {1, 1}},
     {{0, -1}, {0, 0}, {1, 0}, {1, 1}},
     {{-1, 0}, {0, 0}, {0, 1}, {1, 1}}},
    // Z_SHAPE
    {{{1, -1}, {1, 0}, {0, 0}, {0, 1}},
     {{-1, 1}, {0, 1}, {0, 0}, {1, 0}},
     {{1, -1}, {1, 0}, {0, 0}, {0, 1}},
     {{-1, 1}, {0, 1}, {0, 0}, {1, 0}}},
    // J_SHAPE
    {{{0, -1}, {0, 0}, {0, 1}, {1, -1}},
     {{-1, 0}, {0, 0}, {1, 0}, {1, 1}},
     {{0, -1}, {0, 0}, {0, 1}, {-1, 1}},
     {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}},
    // L_SHAPE
    {{{0, -1}, {0, 0}, {0, 1}, {1, 1}},
     {{-1, 1}, {0, 1}, {1, 1}, {1, 0}},
     {{0, -1}, {0, 0}, {0, 1}, {-1, -1}},
     {{-1, 0}, {0, 0}, {1, 0}, {1, -1}}}};

// Function Prototypes
void init_tetris(TetrisGame *game);
void rotate_piece(TetrisGame *game);
void move_piece_left(TetrisGame *game);
void move_piece_right(TetrisGame *game);
int move_piece_down(TetrisGame *game);
void clear_rows(TetrisGame *game);
void update_game(TetrisGame *game);
void lock_piece(TetrisGame *game);
bool spawn_new_piece(TetrisGame *game);

// Function prototypes for internal collision checks
bool piece_reached_bottom(TetrisGame *game);
bool piece_collides(TetrisGame *game);

void load_max_score(TetrisGame *game);
void save_max_score(TetrisGame *game);

#endif  // TETRIS_H
