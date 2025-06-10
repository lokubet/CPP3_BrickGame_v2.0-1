#ifndef SRC_BRICK_GAME_SNAKE_S21_SNAKE_CONTROLLER_H_
#define SRC_BRICK_GAME_SNAKE_S21_SNAKE_CONTROLLER_H_

#include "../brick_game/snake/snake.h"
#include "../gui/cli/snake/snake_gui.h"

class SnakeLogic;

namespace s21 {

class snakeController {
 public:
  void getDirection(SnakeLogic &snakeLogic);
  void run();
  void pauseGame();
  void displayGameOver();
};

}  // namespace s21

#endif  // SRC_BRICK_GAME_SNAKE_S21_SNAKE_CONTROLLER_H_