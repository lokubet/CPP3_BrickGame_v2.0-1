#ifndef GUI_CLI_S21_SNAKE_GUI_H_
#define GUI_CLI_S21_SNAKE_GUI_H_

#include "../../../brick_game/snake/snake.h"

#define CLI_WIDTH 35   // Width of the terminal UI
#define CLI_HEIGHT 25  // Height of the terminal UI

class SnakeLogic;

namespace s21 {

class snakeFront {
 private:
  SnakeLogic &snakeLogic;

 public:
  snakeFront(SnakeLogic &logic);
  ~snakeFront();

  void draw();
};

}  // namespace s21

#endif  // GUI_CLI_S21_SNAKE_GUI_H_
