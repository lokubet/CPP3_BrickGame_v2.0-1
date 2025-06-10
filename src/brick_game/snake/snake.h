#ifndef BRICK_GAME_SNAKE_S21_SNAKE_H_
#define BRICK_GAME_SNAKE_S21_SNAKE_H_

#include <ncurses.h>

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include "../../controllerSnake/snake_controller.h"

namespace s21 {
class snakeController;
}

namespace s21 {

class SnakeLogic {
  friend class snakeController;

 private:
  int score = 0;
  int speed;
  bool gameOver = true;

  const int width = 10;
  const int height = 20;

 public:
  int currentScore;
  int maxScore;
  int currentLevel;
  const int maxLevel = 10;
  const std::string maxScoreFilePath = "SnakeScore.txt";

  enum Direction { UP, DOWN, LEFT, RIGHT };
  int dir = UP;

  void setDirectionValue(int value) { dir = value; }

  int getDirectionValue() { return dir; }

  struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator!=(const Point &other) const {
      return x != other.x || y != other.y;
    }

    bool operator==(const Point &other) const {
      return x == other.x || y == other.y;
    }
  };

  std::vector<Point> snake;
  Point apple;

  SnakeLogic();

  void move();
  void checkCollision();
  void spawnApple();
  void checkApple();
  bool checkSnake(Point pos);

  void updateScore();
  void loadMaxScore();
  void saveMaxScore();
  void increaseLevel();

  void setMaxScore(int newMaxScore) { maxScore = newMaxScore; }

  int getWidth() const { return width; }

  int getHeight() const { return height; }

  int getCurrentScore() const { return currentScore; }

  int getMaxScore() const { return maxScore; }

  int getCurrentLevel() const { return currentLevel; }

  std::vector<Point> getSnake() const { return snake; }

  Point getFood() const { return apple; }

  bool getGameOver() const { return gameOver; }

  void setGameOver(bool value) { gameOver = value; }

  int getSpeed() const { return speed; };

  void setCurrentScore(int newScore) { currentScore = newScore; }

  void setCurrentLevel(int newLevel) { currentLevel = newLevel; }

  void setSpeed(int newSpeed) { speed = newSpeed; }

  void setFood(const Point &newFoodPosition) { apple = newFoodPosition; }
};
}  // namespace s21

#endif  // BRICK_GAME_SNAKE_S21_SNAKE_H_
