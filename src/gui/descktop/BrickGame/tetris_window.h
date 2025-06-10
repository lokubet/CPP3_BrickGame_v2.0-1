#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H

#undef border
#include <QtGui/qtextcursor.h>

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QtWidgets/QLineEdit>

#ifdef __cplusplus
extern "C" {
#endif
#include "../../../brick_game/tetris/tetris.h"  // Include your game logic
#ifdef __cplusplus
}
#endif

class TetrisWindow : public QMainWindow {
  Q_OBJECT

 public:
  TetrisWindow(QWidget *parent = nullptr);
  ~TetrisWindow();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void updateGame();

 private:
  void drawPlayfield(QPainter &painter);
  void drawPiece(QPainter &painter, const Piece &piece);
  void drawSidebar(QPainter &painter);
  void drawGameOver(QPainter &painter);
  void drawPause(QPainter &painter);

  TetrisGame game;
  QTimer *gameTimer;
  const int blockSize = 30;  // Size of each block in the playfield
};

#endif  // TETRISWINDOW_H
