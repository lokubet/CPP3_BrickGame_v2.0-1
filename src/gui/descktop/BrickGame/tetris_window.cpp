#include "tetris_window.h"

#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>

TetrisWindow::TetrisWindow(QWidget *parent)
    : QMainWindow(parent), gameTimer(new QTimer(this)) {
  setFixedSize(500, 600);  // Set fixed window size
  init_tetris(&game);      // Initialize the Tetris game

  // Setup a timer to call updateGame periodically
  connect(gameTimer, &QTimer::timeout, this, &TetrisWindow::updateGame);
  gameTimer->start(500);  // Adjust the interval as needed
}

TetrisWindow::~TetrisWindow() { delete gameTimer; }

void TetrisWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  if (game.state == GAME_OVER) {
    drawGameOver(painter);
  } else if (game.state == PAUSED) {
    drawPause(painter);
  } else {
    drawPlayfield(painter);
    drawSidebar(painter);
    drawPiece(painter, game.current_piece);  // Draw the current piece
  }
}

void TetrisWindow::keyPressEvent(QKeyEvent *event) {
  if (game.state == GAME_OVER) {
    return;  // No input handling when game is over
  }

  switch (event->key()) {
    case Qt::Key_Left:
      move_piece_left(&game);
      break;
    case Qt::Key_Right:
      move_piece_right(&game);
      break;
    case Qt::Key_Down:
      move_piece_down(&game);
      break;
    case Qt::Key_Up:
      rotate_piece(&game);
      break;
    case Qt::Key_Space:
      game.state = (game.state == PAUSED) ? PLAYING : PAUSED;
      break;
    case Qt::Key_P:  // Pause game
      game.state = (game.state == PAUSED) ? PLAYING : PAUSED;
      break;
    case Qt::Key_Q:          // Exit game
      QApplication::quit();  // Exit application
      break;
    default:
      QWidget::keyPressEvent(event);
  }
  update();  // Request a repaint
}

void TetrisWindow::updateGame() {
  if (game.state == PLAYING) {
    update_game(&game);  // Update game logic
    update();            // Request a repaint after the game state is updated
  }
}

// Draw the Tetris playfield
void TetrisWindow::drawPlayfield(QPainter &painter) {
  painter.setBrush(Qt::gray);
  for (int y = 0; y < FIELD_HEIGHT; ++y) {
    for (int x = 0; x < FIELD_WIDTH; ++x) {
      if (game.field[y][x]) {
        painter.setBrush(Qt::red);  // Set block color
      } else {
        painter.setBrush(Qt::gray);  // Set empty color
      }
      painter.drawRect(x * blockSize, y * blockSize, blockSize, blockSize);
    }
  }
}

// Draw a specific Tetris piece
void TetrisWindow::drawPiece(QPainter &painter, const Piece &piece) {
  painter.setBrush(Qt::green);  // Set the color for the piece
  for (int i = 0; i < 4; ++i) {
    int x = piece.positions[i].x;
    int y = piece.positions[i].y;
    painter.drawRect(x * blockSize, y * blockSize, blockSize, blockSize);
  }
}

// Draw the sidebar with score, next piece, etc.
void TetrisWindow::drawSidebar(QPainter &painter) {
  painter.setPen(Qt::black);
  painter.setFont(QFont("Arial", 12));

  // Draw Score
  painter.drawText(FIELD_WIDTH * blockSize + 10, 50,
                   "Score: " + QString::number(game.score));
  painter.drawText(FIELD_WIDTH * blockSize + 10, 80,
                   "Level: " + QString::number(game.level));

  // Draw Next Piece label
  painter.drawText(FIELD_WIDTH * blockSize + 10, 150, "Next Piece:");
  drawPiece(painter, game.next_piece);
}

// Draw Game Over screen
void TetrisWindow::drawGameOver(QPainter &painter) {
  painter.setFont(QFont("Arial", 20));
  painter.setPen(Qt::red);
  painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
}

// Draw Pause screen
void TetrisWindow::drawPause(QPainter &painter) {
  painter.setFont(QFont("Arial", 20));
  painter.setPen(Qt::yellow);
  painter.drawText(rect(), Qt::AlignCenter, "PAUSED");
}
