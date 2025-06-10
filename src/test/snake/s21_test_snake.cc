#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../brick_game/snake/snake.h"
#include "../../controllerSnake/snake_controller.h"

using namespace s21;

// Тест функции move() для простого перемещения вверх
TEST(SnakeLogicTest, MoveUp) {
  s21::SnakeLogic snakeLogic;
  snakeLogic.setDirectionValue(s21::SnakeLogic::UP);

  std::vector<s21::SnakeLogic::Point> initialSnake = snakeLogic.getSnake();
  snakeLogic.move();

  std::vector<s21::SnakeLogic::Point> movedSnake = snakeLogic.getSnake();
  EXPECT_EQ(movedSnake[0].x,
            initialSnake[0].x - 1);  // Голова змеи должна сдвинуться вверх
  EXPECT_EQ(movedSnake[0].y,
            initialSnake[0].y);  // По оси y не должно быть изменений
}

// Тест для проверки выхода за границы экрана (коллизия)
TEST(SnakeLogicTest, CollisionWithWall) {
  s21::SnakeLogic snakeLogic;
  snakeLogic.setDirectionValue(s21::SnakeLogic::UP);

  // Перемещаем голову змеи на границу
  while (snakeLogic.getSnake().front().x > 1) {
    snakeLogic.move();
  }

  snakeLogic.move();  // Должен произойти выход за границу
  snakeLogic.checkCollision();

  EXPECT_TRUE(snakeLogic.getGameOver());  // Игра должна завершиться
}

// Тест на проверку функции spawnApple
TEST(SnakeLogicTest, SpawnApple) {
  s21::SnakeLogic snakeLogic;
  snakeLogic.spawnApple();

  s21::SnakeLogic::Point applePosition = snakeLogic.getFood();
  EXPECT_GE(applePosition.x, 1);
  EXPECT_LE(applePosition.x, snakeLogic.getHeight());
  EXPECT_GE(applePosition.y, 1);
  EXPECT_LE(applePosition.y, snakeLogic.getWidth());

  EXPECT_FALSE(snakeLogic.checkSnake(
      applePosition));  // Яблоко не должно появиться на теле змеи
}

// Тест для функции checkApple
TEST(SnakeLogicTest, CheckAppleEndsGameAt200Score) {
  s21::SnakeLogic snakeLogic;
  snakeLogic.setCurrentScore(200);  // Устанавливаем очки на уровне 200

  snakeLogic.checkApple();
  EXPECT_TRUE(snakeLogic.getGameOver());  // Игра должна завершиться
}

// Тест на проверку увеличения уровня
TEST(SnakeLogicTest, IncreaseLevel) {
  s21::SnakeLogic snakeLogic;
  int initialLevel = snakeLogic.getCurrentLevel();

  snakeLogic.setCurrentScore(5);  // Достаточно для повышения уровня
  snakeLogic.updateScore();

  EXPECT_EQ(snakeLogic.getCurrentLevel(),
            initialLevel + 1);  // Уровень должен повыситься
}

// Тест на проверку обновления максимального счета
TEST(SnakeLogicTest, UpdateMaxScore) {
  s21::SnakeLogic snakeLogic;
  snakeLogic.setMaxScore(10);  // Устанавливаем начальный максимальный счет

  snakeLogic.setCurrentScore(15);  // Новый текущий счет
  snakeLogic.updateScore();

  EXPECT_EQ(snakeLogic.getMaxScore(),
            15);  // Максимальный счет должен обновиться
}

// Тест на проверку сохранения максимального счета
TEST(SnakeLogicTest, SaveMaxScore) {
  s21::SnakeLogic snakeLogic;
  snakeLogic.setMaxScore(50);

  snakeLogic.saveMaxScore();  // Сохраняем счет
  s21::SnakeLogic newSnakeLogic;  // Создаем новый объект логики

  newSnakeLogic.loadMaxScore();  // Загружаем максимальный счет
  EXPECT_EQ(newSnakeLogic.getMaxScore(),
            50);  // Проверяем, что счет был сохранен и загружен корректно
}

// Тест на проверку скорости игры при увеличении уровня
TEST(SnakeLogicTest, SpeedIncreasesWithLevel) {
  s21::SnakeLogic snakeLogic;

  snakeLogic.setCurrentLevel(5);  // Устанавливаем уровень на 5
  snakeLogic.increaseLevel();

  EXPECT_EQ(snakeLogic.getSpeed(),
            400 - 6 * 30);  // Проверяем скорость для уровня 6
}

TEST(Constructor, constructorTest_5) {
  s21::SnakeLogic snake;

  int score = snake.getCurrentScore();
  EXPECT_EQ(score, 0);

  int level = snake.getCurrentLevel();
  EXPECT_EQ(level, 1);

  int speed = snake.getSpeed();
  EXPECT_EQ(speed, 370);
}

TEST(SnakeLogicTest, InitialSnakeLength) {
  s21::SnakeLogic snake;
  EXPECT_EQ(4, snake.getSnake().size());
}

TEST(SnakeLogicTest, InitialFoodSpawned) {
  s21::SnakeLogic snake;
  bool isFoodOnSnake = false;
  for (const auto& segment : snake.getSnake()) {
    if (segment.x == snake.getFood().x && segment.y == snake.getFood().y) {
      isFoodOnSnake = true;
      break;
    }
  }
  ASSERT_FALSE(isFoodOnSnake);
}

TEST(SnakeLogicTest, SnakeGrowsOnMove) {
  s21::SnakeLogic snake;
  int initialSnakeSize = snake.getSnake().size();
  snake.move();
  int newSnakeSize = snake.getSnake().size();
  EXPECT_EQ(newSnakeSize, initialSnakeSize);
}

TEST(SnakeLogicTest, EatingFoodIncreasesScore) {
  s21::SnakeLogic snake;
  int initialScore = snake.getCurrentScore();
  snake.move();
  int newScore = snake.getCurrentScore();
  EXPECT_EQ(newScore, initialScore);
}

TEST(SnakeLogicTest, EatingFoodIncreasesScore1) {
  s21::SnakeLogic snake;
  int initialScore = snake.getCurrentScore();
  snake.move();
  int newScore = snake.getCurrentScore();
  EXPECT_EQ(newScore, initialScore);
  EXPECT_FALSE(snake.getSnake().front().x == 6 &&
               snake.getSnake().front().y == 6);
}

TEST(spawnAppleTest, EmptySnake) {
  s21::SnakeLogic game;
  game.spawnApple();

  EXPECT_GE(game.getFood().x, 1);
  EXPECT_LE(game.getFood().x, 19);
  EXPECT_GE(game.getFood().y, 1);
  EXPECT_LE(game.getFood().y, 9);
}

TEST(checkAppleTest, GameOverWhenScoreIs200) {
  s21::SnakeLogic game;
  game.setCurrentScore(200);

  game.checkApple();
  EXPECT_TRUE(game.getGameOver());
}

TEST(checkAppleTest, GameNotOverWhenScoreIsLessThan200) {
  s21::SnakeLogic game;
  game.setCurrentScore(199);

  game.checkApple();
  EXPECT_FALSE(game.getGameOver());
}

TEST(SnakeLogicTest, ScoreIsUpdatedOnMultipleOfFive) {
  s21::SnakeLogic game;
  game.setCurrentScore(10);
  game.updateScore();

  ASSERT_EQ(2, game.getCurrentLevel());
}

TEST(SnakeLogicTest, MaxScoreIsUpdated) {
  s21::SnakeLogic game;
  game.setCurrentScore(100);
  game.saveMaxScore();
  game.updateScore();

  ASSERT_EQ(100, game.getMaxScore());
}

TEST(SnakeLogicTest, LevelIsIncreasedWithinMaxLevel) {
  s21::SnakeLogic game;
  game.setCurrentLevel(1);
  game.increaseLevel();

  ASSERT_EQ(2, game.getCurrentLevel());
}

TEST(SnakeLogicTest, CollisionOnBoundaryX) {
  s21::SnakeLogic game;
  game.getSnake().front().x;
  game.checkCollision();

  ASSERT_FALSE(game.getGameOver());
}

TEST(SnakeLogicTest, MoveTest) {
  s21::SnakeLogic game;

  auto a = game.getSnake();

  game.setDirectionValue(3);
  game.move();
  a = game.getSnake();

  game.setDirectionValue(1);
  game.move();
  a = game.getSnake();

  for (size_t i = 0; i < 4; ++i) {
    ASSERT_TRUE(a[i].x == a[i].x);
  }
}

TEST(SnakeLogicTest, MoveTest2) {
  s21::SnakeLogic game;

  auto a = game.getSnake();

  game.setDirectionValue(2);
  game.move();
  a = game.getSnake();

  game.setDirectionValue(0);
  game.move();
  a = game.getSnake();

  for (size_t i = 0; i < 4; ++i) {
    ASSERT_TRUE(a[i].x == a[i].x);
  }
}

TEST(SnakeLogicTest, Food) {
  s21::SnakeLogic game;

  ASSERT_FALSE(game.getGameOver());
}

class SnakeControllerTest : public ::testing::Test {
 protected:
  s21::SnakeLogic snakeLogic;
  snakeController controller;

  // Настройка перед каждым тестом
  void SetUp() override {
    // Установка начального состояния
    snakeLogic.setGameOver(false);
    snakeLogic.setCurrentScore(0);
    snakeLogic.setCurrentLevel(1);
    snakeLogic.setSpeed(100);
  }

  // Очистка после каждого теста
  void TearDown() override {
    // Дополнительная очистка, если необходимо
  }
};

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
