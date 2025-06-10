#include "../../brick_game/snake/snake.h"
#include "../../controllerSnake/snake_controller.h"  // Include the snake game controller

#ifdef __cplusplus
extern "C" {
#include "../../brick_game/tetris/tetris.c"
#include "../../brick_game/tetris/tetris.h"
#include "tetris/cli.c"
#include "tetris/cli.h"
}
#endif  //_cplusplus

#include <sys/time.h>
#include <time.h>

// Function to handle the Tetris game loop
void run_tetris() {
  TetrisGame game;
  init_tetris(&game);  // Initialize game state and load high score
  init_cli();          // Initialize ncurses

  WINDOW *win = newwin(PLAYFIELD_HEIGHT + 2, PLAYFIELD_WIDTH + 2, 0, 0);
  box(win, 0, 0);  // Draw border

  long long last_update_time = current_time_ms();
  const long long tick_duration = 100;
  nodelay(stdscr, TRUE);  // Non-blocking input

  while (1) {
    long long current_time = current_time_ms();
    char input = handle_input(&game);

    if (input == 'q') {
      game.state = GAME_OVER;
    }

    if (input == 'z') {
      rotate_piece(&game);
    }

    if (current_time - last_update_time >= tick_duration) {
      last_update_time = current_time;

      switch (game.state) {
        case MENU:
          draw_start_screen();
          break;
        case PLAYING:
          draw_game(&game, win);
          update_game(&game);
          break;
        case PAUSED:
          draw_pause_screen();
          break;
        case GAME_OVER:
          if (game.score > game.max_score) {
            game.max_score = game.score;
            save_max_score(&game);
          }
          draw_game_over_screen();
          timeout(-1);  // Wait indefinitely for input
          if (getch() == 'q') {
            close_cli();
            return;
          }
          break;
      }
    }
  }
  close_cli();
}

void run_snake() {
  s21::snakeController snakeController;
  snakeController.run();  // This function runs the Snake game
}

int main() {
  srand(time(NULL));  // Seed the random number generator
  initscr();          // Initialize ncurses
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);  // Non-blocking input
  noecho();               // Disable echoing of characters

  while (1) {
    clear();
    mvprintw(1, 1, "Welcome to the Arcade Game!");
    mvprintw(3, 1, "1. Tetris Game");
    mvprintw(5, 1, "2. Snake Game");
    mvprintw(7, 1, "3. Exit");
    refresh();

    int choice = getch();
    switch (choice) {
      case '1':  // Run Snake game
        run_tetris();
        break;
      case '2':  // Run Tetris game
        run_snake();
        break;
      case '3':    // Exit
        endwin();  // End ncurses mode
        return 0;
    }
  }

  endwin();  // Cleanup ncurses on exit
  return 0;
}
