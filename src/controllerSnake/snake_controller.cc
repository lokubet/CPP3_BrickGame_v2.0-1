#ifndef SRC_BRICK_GAME_SNAKE_S21_SNAKE_CONTROLLER_CC
#define SRC_BRICK_GAME_SNAKE_S21_SNAKE_CONTROLLER_CC

#include "snake_controller.h"
namespace s21 {

void snakeController::getDirection(SnakeLogic &snakeLogic) {
  int key = getch();

  switch (key) {
    case 'w':
    case 'W':
      snakeLogic.setDirectionValue(0);  // вверх
      break;
    case 's':
    case 'S':
      snakeLogic.setDirectionValue(1);  // вниз
      break;
    case 'a':
    case 'A':
      snakeLogic.setDirectionValue(2);  // влево
      break;
    case 'd':
    case 'D':
      snakeLogic.setDirectionValue(3);  // вправо
      break;

    case 'p':
    case 'P':
      pauseGame();  // вызываем функцию для паузы
      break;

    case 'q':
    case 'Q':
      displayGameOver();
      snakeLogic.setGameOver(true);  // выход из игры
      break;

    default:
      break;
  }

  flushinp();  // очищаем буфер ввода
}

// Функция паузы
void snakeController::pauseGame() {
  mvprintw(0, 0, "Game paused. Press 'P' to resume.");

  while (true) {
    int resumeKey = getch();
    if (resumeKey == 'p' || resumeKey == 'P') {
      break;
    }
  }

  mvprintw(0, 0, "                      ");
  refresh();
}

void snakeController::displayGameOver() {
  clear();

  mvprintw(CLI_HEIGHT / 2, (CLI_WIDTH / 2) - 5, "GAME OVER");
  mvprintw(CLI_HEIGHT / 2 + 1, (CLI_WIDTH / 2) - 13, "Press 'q' to Quit");

  refresh();

  while (true) {
    int key = getch();
    if (key == 'q' || key == 'Q') {
      break;
    }
  }
}

void snakeController::run() {
  SnakeLogic game;
  snakeFront gameRenderer(game);

  while (!game.getGameOver()) {
    gameRenderer.draw();

    getDirection(game);

    game.move();

    game.checkCollision();
    game.checkApple();

    std::this_thread::sleep_for(std::chrono::milliseconds(game.getSpeed()));
  }
}
}  // namespace s21

#endif