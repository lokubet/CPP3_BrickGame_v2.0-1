#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>

#include "snake_window.h"
#include "tetris_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_Exit_Button_clicked();

  void on_Snake_Button_clicked();

  void on_Tetris_Button_clicked();

 private:
  Ui::MainWindow *ui;
  QWidget *info;
  s21::SnakeLogic *game;
};
#endif  // MAINWINDOW_H
