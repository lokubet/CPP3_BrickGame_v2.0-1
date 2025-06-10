QT += core gui

greaterThan(QT_MAJOR_VERSION, 5)
    : QT += widgets

          CONFIG += c++ 17

      LIBS += -lncurses

#You can make your code fail to compile if it uses deprecated APIs.
#In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE = \
    0x060000 #disables all the APIs deprecated before Qt 6.0.0

                  SOURCES +=
          ../../../ brick_game / snake / snake.cc../../../ gui / cli / snake /
          snake_gui.cc../../../ brick_game / tetris / tetris.c../../../
          controllerSnake /
          snake_controller.cc main.cpp mainwindow.cpp snake_window
          .cpp tetris_window.cpp

              HEADERS +=../../../ brick_game / snake / snake.h../../../
                        brick_game / tetris / tetris.h../../../
                        controllerSnake /
                        snake_controller.h mainwindow.h snake_window
          .h tetris_window.h tetris_wrapper.h

                            FORMS += mainwindow
          .ui

#Default rules for deployment.
                                         qnx : target.path =
                            / tmp / $${TARGET} /
                            bin else : unix : !android : target.path =
                                / opt / $${TARGET} /
                                bin !isEmpty(target.path) : INSTALLS += target
