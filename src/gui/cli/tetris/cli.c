// gui/cli/cli.c

#include "cli.h"

#include <sys/time.h>
#include <time.h>

// Initialize the CLI (ncurses)
void init_cli() {
  initscr();
  cbreak();
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  timeout(0);
  start_color();
  init_pair(COLOR_PAIR_PIECE, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_PAIR_BORDER, COLOR_WHITE, COLOR_BLACK);
  init_pair(COLOR_PAIR_TEXT, COLOR_YELLOW, COLOR_BLACK);
}

// Close the CLI (ncurses)
void close_cli() { endwin(); }

// Draw the playfield
void draw_playfield(TetrisGame *game, WINDOW *win) {
  werase(win);
  box(win, 0, 0);

  for (int y = 0; y < PLAYFIELD_HEIGHT; y++) {
    for (int x = 0; x < PLAYFIELD_WIDTH; x++) {
      if (game->field[y][x]) {
        wattron(win, COLOR_PAIR(COLOR_PAIR_PIECE));
        mvwprintw(win, y + 1, x + 1, "*");
        wattroff(win, COLOR_PAIR(COLOR_PAIR_PIECE));
      }
    }
  }

  Piece *piece = &game->current_piece;
  for (int i = 0; i < 4; i++) {
    int px = piece->positions[i].x;
    int py = piece->positions[i].y;
    if (px >= 0 && px < PLAYFIELD_WIDTH && py >= 0 && py < PLAYFIELD_HEIGHT) {
      wattron(win, COLOR_PAIR(COLOR_PAIR_PIECE));
      mvwprintw(win, py + 1, px + 1, "*");
      wattroff(win, COLOR_PAIR(COLOR_PAIR_PIECE));
    }
  }

  wrefresh(win);
}

// Draw the start screen
void draw_start_screen() {
  clear();
  mvprintw(CLI_HEIGHT / 2, (CLI_WIDTH / 2) - 5, "START");
  mvprintw(CLI_HEIGHT / 2 + 1, (CLI_WIDTH / 2) - 12, "Press SPACE to Start");
  refresh();
}

// Draw the pause screen
void draw_pause_screen() {
  clear();
  mvprintw(CLI_HEIGHT / 2, (CLI_WIDTH / 2) - 7, "GAME PAUSED");
  mvprintw(CLI_HEIGHT / 2 + 1, (CLI_WIDTH / 2) - 14, "Press SPACE to Resume");
  refresh();
}

// Draw the game over screen
void draw_game_over_screen() {
  clear();
  mvprintw(CLI_HEIGHT / 2, (CLI_WIDTH / 2) - 5, "GAME OVER");
  mvprintw(CLI_HEIGHT / 2 + 1, (CLI_WIDTH / 2) - 13, "Press 'q' to Quit");
  refresh();
}

// Draw the sidebar with score, level, high score, and next piece
void draw_sidebar(TetrisGame *game) {
  int x_offset = PLAYFIELD_WIDTH + 3;
  int y_offset = 2;

  wattron(stdscr, COLOR_PAIR(COLOR_PAIR_TEXT));
  mvprintw(y_offset, x_offset, "Score: %d", game->score);
  mvprintw(y_offset + 2, x_offset, "Level: %d", game->level);
  mvprintw(y_offset + 4, x_offset, "Highscore: %d", game->max_score);
  mvprintw(y_offset + 6, x_offset, "Next:");

  Piece *next_piece = &game->next_piece;
  // Define a fixed position for the next piece display
  int display_x = x_offset + 2;
  int display_y = y_offset + 8;

  // Optional: Clear the previous next piece display area
  for (int i = 0; i < 4; i++) {
    mvprintw(display_y + i, display_x, "      ");  // Adjust spacing as needed
  }

  for (int i = 0; i < 4; i++) {
    int px = next_piece->positions[i].x - (FIELD_WIDTH / 2 - 2) + 1;
    int py = next_piece->positions[i].y + 1;

    // Adjust to display coordinates
    int final_x = display_x + px;
    int final_y = display_y + py;

    // Ensure the coordinates are within the sidebar display area
    if (final_x >= display_x && final_x < (display_x + 5) &&
        final_y >= display_y && final_y < (display_y + 5)) {
      wattron(stdscr, COLOR_PAIR(COLOR_PAIR_PIECE));
      mvprintw(final_y, final_x, "*");
      wattroff(stdscr, COLOR_PAIR(COLOR_PAIR_PIECE));
    }
  }

  wattroff(stdscr, COLOR_PAIR(COLOR_PAIR_TEXT));
}

// Draw the entire game screen
void draw_game(TetrisGame *game, WINDOW *win) {
  draw_playfield(game, win);
  draw_sidebar(game);
  refresh();
}

// Get the current time in milliseconds
long long current_time_ms() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (ts.tv_sec * 1000LL) + (ts.tv_nsec / 1000000LL);
}

// Handle user input
char handle_input(TetrisGame *game) {
  int ch = getch();
  switch (ch) {
    case ' ':
      if (game->state == MENU) {
        clear();
        game->state = PLAYING;
      }
      if (game->state == PAUSED) {
        clear();
        game->state = PLAYING;
      }
      break;
    case KEY_LEFT:
      move_piece_left(game);
      break;
    case KEY_RIGHT:
      move_piece_right(game);
      break;
    case KEY_DOWN:
      move_piece_down(game);
      break;
    case 'z':
    case 'Z':
      rotate_piece(game);
      break;
    case 'p':
    case 'P':
      game->state = PAUSED;
      break;
    case 'q':
    case 'Q':
      return 'q';  // Exit flag
    default:
      break;
  }
  return 0;  // No command
}
