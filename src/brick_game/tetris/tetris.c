#include "tetris.h"

// Initialize the Tetris game
void init_tetris(TetrisGame *game) {
  game->state = MENU;
  memset(game->field, 0, sizeof(game->field));
  game->score = 0;
  game->max_score = 0;
  game->level = 1;
  load_max_score(game);  // Load the high score at initialization

  // Initialize current_piece as empty
  memset(&game->current_piece, 0, sizeof(Piece));

  // Generate the first next_piece
  int initial_piece_type = rand() % NUM_PIECES;
  game->next_piece.type = initial_piece_type;
  game->next_piece.rotation = 0;
  for (int i = 0; i < 4; ++i) {
    game->next_piece.positions[i].x =
        PIECES[initial_piece_type][0][i].x + FIELD_WIDTH / 2 - 2;
    game->next_piece.positions[i].y = PIECES[initial_piece_type][0][i].y;
  }

  // Spawn the first current_piece
  spawn_new_piece(game);
}

// Rotate the current piece
void rotate_piece(TetrisGame *game) {
  Piece *piece = &game->current_piece;
  int new_rotation = (piece->rotation + 1) % 4;
  Point new_positions[4];

  for (int i = 0; i < 4; ++i) {
    new_positions[i] = PIECES[piece->type][new_rotation][i];
    new_positions[i].x += piece->positions[0].x;
    new_positions[i].y += piece->positions[0].y;
  }

  for (int i = 0; i < 4; ++i) {
    if (new_positions[i].x < 0 || new_positions[i].x >= FIELD_WIDTH ||
        new_positions[i].y < 0 || new_positions[i].y >= FIELD_HEIGHT ||
        game->field[new_positions[i].y][new_positions[i].x]) {
      return;  // Rotation invalid
    }
  }

  for (int i = 0; i < 4; ++i) {
    piece->positions[i] = new_positions[i];
  }
  piece->rotation = new_rotation;
}

// Move the current piece left
void move_piece_left(TetrisGame *game) {
  Piece *piece = &game->current_piece;
  Point new_positions[4];
  int step = -1;
  for (int i = 0; i < 4; ++i) {
    new_positions[i].x = piece->positions[i].x + step;
    new_positions[i].y = piece->positions[i].y;
    if (new_positions[i].x < 0 || new_positions[i].x >= FIELD_WIDTH ||
        game->field[new_positions[i].y][new_positions[i].x]) {
      return;  // Move invalid
    }
  }
  for (int i = 0; i < 4; ++i) {
    piece->positions[i] = new_positions[i];
  }
}

// Move the current piece right
void move_piece_right(TetrisGame *game) {
  Piece *piece = &game->current_piece;
  Point new_positions[4];
  int step = 1;
  for (int i = 0; i < 4; ++i) {
    new_positions[i].x = piece->positions[i].x + step;
    new_positions[i].y = piece->positions[i].y;
    if (new_positions[i].x < 0 || new_positions[i].x >= FIELD_WIDTH ||
        game->field[new_positions[i].y][new_positions[i].x]) {
      return;  // Move invalid
    }
  }
  for (int i = 0; i < 4; ++i) {
    piece->positions[i] = new_positions[i];
  }
}

// Move the current piece down
int move_piece_down(TetrisGame *game) {
  Piece *piece = &game->current_piece;
  Point new_positions[4];
  for (int i = 0; i < 4; ++i) {
    new_positions[i].x = piece->positions[i].x;
    new_positions[i].y = piece->positions[i].y + 1;
    if (new_positions[i].y >= FIELD_HEIGHT ||
        game->field[new_positions[i].y][new_positions[i].x] == true)
      return false;  // Cannot move down
  }
  for (int i = 0; i < 4; ++i) {
    piece->positions[i] = new_positions[i];
  }
  return true;
}

// Clear full rows and update score
void clear_rows(TetrisGame *game) {
  int rows_cleared = 0;
  for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
    bool lineFull = true;
    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      if (game->field[i][j] == 0) {
        lineFull = false;
        break;
      }
    }
    if (lineFull) {
      rows_cleared++;
      for (int k = i; k > 1; k--) {
        for (int j = 1; j < FIELD_WIDTH - 1; j++) {
          game->field[k][j] = game->field[k - 1][j];
        }
      }
      for (int j = 1; j < FIELD_WIDTH - 1; j++) {
        game->field[1][j] = 0;  // Clear the top row after shifting
      }
    }
  }
  switch (rows_cleared) {
    case 1:
      game->score += 100;
      break;
    case 2:
      game->score += 300;
      break;
    case 3:
      game->score += 700;
      break;
    case 4:
      game->score += 1500;
      break;
    default:
      break;
  }
  if (game->score / 600 > game->level - 1) {
    game->level++;
  }
}

// Lock the current piece into the field
void lock_piece(TetrisGame *game) {
  Piece *piece = &game->current_piece;
  for (int i = 0; i < 4; i++) {
    int x = piece->positions[i].x;
    int y = piece->positions[i].y;
    if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
      game->field[y][x] = piece->type + 1;
    }
  }
}

// Spawn a new piece from next_piece and generate a new next_piece
bool spawn_new_piece(TetrisGame *game) {
  // Transfer next_piece to current_piece
  game->current_piece = game->next_piece;

  // Check for collision
  for (int i = 0; i < 4; i++) {
    int x = game->current_piece.positions[i].x;
    int y = game->current_piece.positions[i].y;

    if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH &&
        game->field[y][x] != 0) {
      game->state = GAME_OVER;
      return false;
    }
  }

  // Generate a new next_piece
  int piece_type = rand() % NUM_PIECES;
  game->next_piece.type = piece_type;
  game->next_piece.rotation = 0;
  for (int i = 0; i < 4; ++i) {
    game->next_piece.positions[i].x =
        PIECES[piece_type][0][i].x + FIELD_WIDTH / 2 - 2;
    game->next_piece.positions[i].y = PIECES[piece_type][0][i].y;
  }

  return true;
}

// Update the game state
void update_game(TetrisGame *game) {
  static int drop_delay_counter = 0;
  const int drop_delay = 500;
  const int tick_duration = 100;

  if (piece_reached_bottom(game) || piece_collides(game)) {
    if (drop_delay_counter >= drop_delay) {
      lock_piece(game);
      clear_rows(game);  // Update score and level
      drop_delay_counter = 0;
      if (!spawn_new_piece(game)) {
        // Game Over handled in spawn_new_piece
      }
    } else {
      drop_delay_counter += tick_duration;
    }
  } else {
    drop_delay_counter = 0;
    move_piece_down(game);
  }
}

// Check if the piece has reached the bottom
bool piece_reached_bottom(TetrisGame *game) {
  Piece *piece = &game->current_piece;
  for (int i = 0; i < 4; i++) {
    int x = piece->positions[i].x;
    int y = piece->positions[i].y;
    if (y >= FIELD_HEIGHT - 1 ||
        (y + 1 < FIELD_HEIGHT && game->field[y + 1][x] != 0)) {
      return true;
    }
  }
  return false;
}

// Check if the piece collides with the field
bool piece_collides(TetrisGame *game) {
  Piece *piece = &game->current_piece;
  for (int i = 0; i < 4; i++) {
    int x = piece->positions[i].x;
    int y = piece->positions[i].y;
    if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH &&
        game->field[y][x] != 0) {
      return true;
    }
  }
  return false;
}

// Load the maximum score from a file
void load_max_score(TetrisGame *game) {
  FILE *file = fopen(SCORE_FILE, "r");
  if (file) {
    if (fscanf(file, "%d", &game->max_score) != 1) {
      game->max_score = 0;  // If the file is empty or data is invalid
    }
    fclose(file);
  } else {
    game->max_score = 0;   // File does not exist, set initial value
    save_max_score(game);  // Create the file and write the initial value
  }
}

// Save the maximum score to a file
void save_max_score(TetrisGame *game) {
  FILE *file = fopen(SCORE_FILE, "w");
  if (file) {
    fprintf(file, "%d", game->max_score);
    fclose(file);
  } else {
    perror("Error opening file for writing");
  }
}
