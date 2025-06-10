#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#undef border
#include <QtGui/qtextcursor.h>

#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QtWidgets/QLineEdit>

#include "../../../brick_game/snake/snake.h"
#include "../../../controllerSnake/snake_controller.h"

class SnakeGameWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SnakeGameWidget(QWidget *parent = nullptr);
  ~SnakeGameWidget();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void startGame();
  void stopGame();
  std::thread snakeTimerThread;
  void updateGame();
  void updateInfoWidget();
  void MakePause();

 private:
  s21::SnakeLogic *snakeGame;
  QLabel *infoWidget;
  int cellSize = 20;
  int snakeX = 20;
  int snakeY = 20;
  int score;
  int maxScore;
  int snakeTimerInterval;
  bool snakeTimerRunning;

  bool m_IsPause = false;

  QTimer *timer;
};

#endif  // SNAKE_WINDOW_H
