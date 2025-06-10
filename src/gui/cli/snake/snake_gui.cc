#include "snake_gui.h"

namespace s21 {

snakeFront::snakeFront(SnakeLogic &logic) : snakeLogic(logic) {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);
}

snakeFront::~snakeFront() { endwin(); }

void snakeFront::draw() {
  clear();

  int width = snakeLogic.getWidth();
  int height = snakeLogic.getHeight();
  for (int i = 0; i < width + 2; ++i) {
    mvprintw(0, i * 2, "#");
    mvprintw(height + 1, i * 2, "#");
  }
  for (int i = 1; i <= height; ++i) {
    mvprintw(i, 0, "#");
    mvprintw(i, (width + 1) * 2, "#");
  }

  std::vector<SnakeLogic::Point> snake = snakeLogic.getSnake();
  for (size_t i = 0; i < snake.size(); ++i) {
    mvprintw(snake[i].x, snake[i].y * 2, "o");
  }

  SnakeLogic::Point apple = snakeLogic.getFood();
  mvprintw(apple.x, apple.y * 2, "*");

  mvprintw(1, (width + 4) * 2, "Score: %d", snakeLogic.getCurrentScore());
  mvprintw(3, (width + 4) * 2, "Max Score: %d", snakeLogic.getMaxScore());
  mvprintw(5, (width + 4) * 2, "Level: %d", snakeLogic.getCurrentLevel());
  mvprintw(7, (width + 4) * 2, "p - Paused");
  mvprintw(9, (width + 4) * 2, "q - Exit");
}

}  // namespace s21