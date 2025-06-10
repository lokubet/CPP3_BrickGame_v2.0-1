#include "snake_window.h"

// #include <QPainter>
// #include <QKeyEvent>
// #include <QTimer>
// #include <QMessageBox>

// namespace s21 {

// SnakeWindow::SnakeWindow(SnakeLogic& logic, QWidget *parent)
//     : QWidget(parent), snakeLogic(logic) {
//     setFixedSize(350, 250);
//     gameTimer = new QTimer(this);

//    connect(gameTimer, &QTimer::timeout, this, &SnakeWindow::updateGame);

//    gameTimer->start(snakeLogic.getSpeed());
//}

// SnakeWindow::~SnakeWindow() {
//     delete gameTimer;
// }

// void SnakeWindow::paintEvent(QPaintEvent *event) {
//     Q_UNUSED(event);
//     QPainter painter(this);

//    // Отрисовываем поле
//    drawField(painter);

////        drawSnake(painter);
////        drawApple(painter);
//}

// void SnakeWindow::keyPressEvent(QKeyEvent *event) {
//     switch (event->key()) {
//         case Qt::Key_W:
//             snakeLogic.setDirectionValue(SnakeLogic::UP);
//             break;
//         case Qt::Key_S:
//             snakeLogic.setDirectionValue(SnakeLogic::DOWN);
//             break;
//         case Qt::Key_A:
//             snakeLogic.setDirectionValue(SnakeLogic::LEFT);
//             break;
//         case Qt::Key_D:
//             snakeLogic.setDirectionValue(SnakeLogic::RIGHT);
//             break;
//         case Qt::Key_P:
//             gameTimer->stop();
//             QMessageBox::information(this, "Paused", "Game Paused. Press OK
//             to resume."); gameTimer->start(snakeLogic.getSpeed()); break;
//         case Qt::Key_Q:
//             close();
//             break;
//         default:
//             QWidget::keyPressEvent(event);
//     }
// }

// void SnakeWindow::updateGame() {
//     if (snakeLogic.getGameOver()) {
//         return;  // Прекращаем обновления, если игра окончена
//     }

//    // Делаем первый шаг игры
//    snakeLogic.move();
//    snakeLogic.checkCollision();
//    snakeLogic.checkApple();

//    update();  // Триггерим paintEvent для обновления экрана
//}

// void SnakeWindow::drawField(QPainter &painter) {
//     // Размеры поля
//     int rows = height() / 15;
//     int cols = width() / 15;

//    // Рисуем сетку
//    painter.setPen(QPen(Qt::gray, 1));  // Серые линии для сетки
//    for (int i = 0; i <= rows; ++i) {
//        painter.drawLine(0, i * 15, width(), i * 15);  // Горизонтальные линии
//    }
//    for (int j = 0; j <= cols; ++j) {
//        painter.drawLine(j * 15, 0, j * 15, height());  // Вертикальные линии
//    }
//}

// void SnakeWindow::drawSnake(QPainter &painter) {
//     painter.setBrush(Qt::green);
//     const auto& snakeSegments = snakeLogic.getSnake();

//    // Ensure there are valid segments to draw
//    if (snakeSegments.empty()) return;  // Check if the snake vector is empty
//    to avoid further access

//    for (const auto& segment : snakeSegments) {
//        if (segment.x < 0 || segment.y < 0 || segment.x >= height() ||
//        segment.y >= width()) continue;  // Skip invalid segments (ensure in
//        bounds) painter.drawRect(segment.y * 15, segment.x * 15, 15, 15);  //
//        Draw rect at segment position
//    }
//}

// void SnakeWindow::drawApple(QPainter &painter) {
//     painter.setBrush(Qt::red);
//     const auto& apple = snakeLogic.getFood();

//    if (apple.x >= 0 && apple.y >= 0) {  // Ensure valid coordinates
//        painter.drawEllipse(apple.y * 15, apple.x * 15, 15, 15);
//    }
//}

// void SnakeWindow::drawGameOver(QPainter &painter) {
//     painter.setBrush(Qt::black);
//     painter.setPen(Qt::white);
//     painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
// }

//}  // namespace s21

#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QTimer>

SnakeGameWidget::SnakeGameWidget(QWidget *parent)
    : QWidget(parent),
      snakeGame(new s21::SnakeLogic())

{
  setFixedSize(400, 650);
  setFocus();

  QPushButton *startButton = new QPushButton("Start Game", this);
  startButton->setGeometry(150, 600, 100, 40);
  connect(startButton, &QPushButton::clicked, this,
          &SnakeGameWidget::startGame);

  infoWidget = new QLabel(this);
  infoWidget->setGeometry(260, 0, 140, 650);
  infoWidget->setFont(QFont("Helvetica", 12));
  infoWidget->setStyleSheet("background-color: white; color: black");
  infoWidget->setAlignment(Qt::AlignCenter);

  updateInfoWidget();
}

SnakeGameWidget::~SnakeGameWidget() { delete snakeGame; }

void SnakeGameWidget::paintEvent(QPaintEvent *event) {
  (void)event;

  QPainter painter(this);

  painter.setBrush(Qt::black);
  painter.drawRect(1, 1, 400, 650);

  QColor turquoiseColor = QColor(64, 224, 208);

  for (int i = 1; i < snakeGame->getWidth() + 1; ++i) {
    for (int j = 1; j < snakeGame->getHeight() + 1; ++j) {
      if ((i + j) % 2 == 0) {
        painter.fillRect(i * cellSize, +j * cellSize, cellSize, cellSize,
                         turquoiseColor);
      } else {
        painter.fillRect(i * cellSize, j * cellSize, cellSize, cellSize,
                         Qt::white);
      }
    }
  }

  painter.setBrush(Qt::green);
  for (const auto &block : snakeGame->getSnake()) {
    painter.drawEllipse(block.y * cellSize, block.x * cellSize, cellSize,
                        cellSize);
  }

  s21::SnakeLogic::Point fruitPosition = snakeGame->getFood();
  painter.setBrush(Qt::red);
  painter.drawEllipse(fruitPosition.y * cellSize, fruitPosition.x * cellSize,
                      cellSize, cellSize);

  updateInfoWidget();
}

void SnakeGameWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_W:
      snakeGame->setDirectionValue(0);
      break;
    case Qt::Key_A:
      snakeGame->setDirectionValue(2);
      break;
    case Qt::Key_S:
      snakeGame->setDirectionValue(1);
      break;
    case Qt::Key_D:
      snakeGame->setDirectionValue(3);

      break;
    case Qt::Key_Q:
      this->close();
      break;
    case Qt::Key_P:
      m_IsPause = !m_IsPause;
      MakePause();
      break;
    default:
      QWidget::keyPressEvent(event);
      break;
  }
}

void SnakeGameWidget::MakePause() {
  if (m_IsPause) {
    timer->stop();
  } else {
    timer->start(snakeGame->getSpeed());
  }
}

void SnakeGameWidget::updateGame() {
  if (!snakeGame->getSnake().empty() && !snakeGame->getGameOver()) {
    snakeGame->move();
    snakeGame->checkCollision();
    if (snakeGame->getGameOver()) {
      QMessageBox gameOverMsgBox;
      gameOverMsgBox.setText("Game Over! Your Score: " +
                             QString::number(snakeGame->getCurrentScore()));
      gameOverMsgBox.setStandardButtons(QMessageBox::Ok);
      int ret = gameOverMsgBox.exec();
      if (ret == QMessageBox::Ok) {
        this->close();
      }
      return;
    }

    update();
    const s21::SnakeLogic::Point head = snakeGame->getSnake().front();
    int newSnakeX = head.x * cellSize;
    int newSnakeY = head.y * cellSize;
    if (newSnakeX != snakeX && newSnakeY != snakeY) {
      return;
    }
    snakeX = newSnakeX;
    snakeY = newSnakeY;
  }
}

void SnakeGameWidget::startGame() {
  if (!snakeTimerRunning) {
    snakeTimerRunning = true;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeGameWidget::updateGame);
    timer->start(snakeGame->getSpeed());
  }
}

void SnakeGameWidget::stopGame() { snakeTimerRunning = false; }

void SnakeGameWidget::updateInfoWidget() {
  infoWidget->setText(
      "Level: " + QString::number(snakeGame->getCurrentLevel()) + "\n" +
      "Score: " + QString::number(snakeGame->getCurrentScore()) + "\n" +
      "Max Score: " + QString::number(snakeGame->getMaxScore()) + "\n" +
      "Q - Exit" + "\n" + "P - Paused"

  );
}
