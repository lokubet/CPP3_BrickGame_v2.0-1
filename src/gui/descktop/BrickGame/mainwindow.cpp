#include "mainwindow.h"

#include "../../../brick_game/snake/snake.h"
#include "snake_window.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Tetris_Button_clicked() {
  this->hide();
  TetrisWindow *window_tetris = new TetrisWindow();
  window_tetris->show();
}

void MainWindow::on_Snake_Button_clicked() {
  SnakeGameWidget *gameWidget = new SnakeGameWidget(this);
  gameWidget->show();
  info = new QWidget(gameWidget);
  info->move(300, 30);
  info->resize(270, 540);

  info->show();
}
void MainWindow::on_Exit_Button_clicked() {
  QMessageBox::StandardButton userReply = QMessageBox::question(
      this, "Exit window", "Do you really want to leave the Game?",
      QMessageBox::Yes | QMessageBox::No);
  if (userReply == QMessageBox::Yes) {
    QApplication::quit();
  }
}
