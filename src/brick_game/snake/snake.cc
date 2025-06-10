#include "snake.h"

namespace s21 {
SnakeLogic::SnakeLogic() : currentScore(0), maxScore(0), currentLevel(1) {
  snake.push_back(Point(height / 2, width / 2));
  snake.push_back(Point(height / 2, width / 2 - 1));
  snake.push_back(Point(height / 2, width / 2 - 2));
  snake.push_back(Point(height / 2, width / 2 - 3));

  spawnApple();

  score = 0;
  speed = 400 - currentLevel * 30;
  gameOver = false;

  loadMaxScore();
}

void SnakeLogic::move() {
  Point head = snake.front();
  Point newHead = head;

  switch (dir) {
    case UP:
      newHead.x--;
      break;
    case DOWN:
      newHead.x++;
      break;
    case LEFT:
      newHead.y--;
      break;
    case RIGHT:
      newHead.y++;
      break;
  }

  snake.insert(snake.begin(), newHead);
  if (newHead.x == apple.x && newHead.y == apple.y) {
    currentScore++;
    updateScore();
    spawnApple();
  } else if (!snake.empty()) {
    snake.pop_back();
  }
}

void SnakeLogic::checkCollision() {
  if (snake.empty()) return;

  if (snake.front().x < 1 || snake.front().x >= height || snake.front().y < 1 ||
      snake.front().y >= width) {
    gameOver = true;
  }

  for (size_t i = 1; i < snake.size(); i++) {
    if (snake.front().x == snake[i].x && snake.front().y == snake[i].y) {
      gameOver = true;
      break;
    }
  }
}

void SnakeLogic::spawnApple() {
  if (snake.empty()) {
    gameOver = true;
    return;
  }

  srand(time(NULL));
  do {
    apple = Point(1 + rand() % 19, 1 + rand() % 9);
  } while (checkSnake(apple));
}

void SnakeLogic::checkApple() {
  if (currentScore == 200) {
    gameOver = true;
  }
}

bool SnakeLogic::checkSnake(Point pos) {
  for (const auto& segment : snake) {
    if (segment.x == pos.x && segment.y == pos.y) {
      return true;
    }
  }
  return false;
}

void SnakeLogic::updateScore() {
  if (currentScore % 5 == 0) {
    increaseLevel();
  }

  if (currentScore > maxScore) {
    maxScore = currentScore;
    saveMaxScore();
  }
}

void SnakeLogic::loadMaxScore() {
  std::ifstream file(maxScoreFilePath);
  if (file.is_open()) {
    file >> maxScore;
    file.close();
  }
}

void SnakeLogic::saveMaxScore() {
  std::ofstream file(maxScoreFilePath);
  if (file.is_open()) {
    file << maxScore;
    file.close();
  }
}

void SnakeLogic::increaseLevel() {
  if (currentLevel < maxLevel) {
    currentLevel++;
    speed = 400 - currentLevel * 30;
  }
}

}  // namespace s21
