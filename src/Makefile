# Compiler settings
GCC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Werror -lstdc++ -lncurses
CHECK = -lcheck
TEST_SNAKE = ./test/snake/s21_test_snake
TEST_TETRIS = ./test/tetris/s21_test_tetris.c
OUTPUT_TETRIS=tetris
BACK_TETRIS= ./brick_game/tetris/*.c
FRONT= ./gui/cli/*.c

# Source files
SOURCES_FOR_SNAKE = ./brick_game/snake/snake.cc \
                    ./gui/cli/snake/snake_gui.cc \
                    ./controllerSnake/snake_controller.cc \
                    ./brick_game/tetris/tetris.c \
                    ./gui/cli/tetris/cli.c \
                    ./gui/cli/main.cc

# Targets
all: clean snake test_brickgame gcov_report dist 

# Build the main application
snake: $(SOURCES_FOR_SNAKE)
	$(CXX) $^ -o brickgame $(CFLAGS) $(CHECK) 

test_brickgame: clean
	g++ -std=c++17 --coverage test/snake/s21_test_snake.cc \
        brick_game/snake/snake.cc \
        controllerSnake/snake_controller.cc \
        gui/cli/snake/snake_gui.cc \
        -lgtest -lncurses -o tests
	./tests

test_tetris:
	$(CC) $(CFLAGS) $(BACK_TETRIS) $(TEST_TETRIS) $(FLAGS) -o $(OUTPUT_TETRIS) -lcheck

# Generate gcov report
gcov_report: test_brickgame
	lcov -t "Coverage Report" --ignore-errors mismatch --output-file res.info -c -d .
	genhtml -o report res.info
	open report/index.html

# Install the application
install: clean
	cd gui/desktop/BrickGame/ && /usr/bin/qmake6 BrickGame.pro && make && make clean && rm Makefile && mkdir -p ../../../build/Desktop-Debug && mv BrickGame ../../../build

# Uninstall the application
uninstall:
	rm -rf ../build dist

# Create distribution package
dist: install
	mkdir -p dist
	cp -R gui/desktop/build/Desktop-Debug/BrickGame ./dist/BrickGame
	cp ./documentation.md ./dist/documentation.md
	cd ./dist && tar cvzf SnakeGame.tgz *
	cd ./dist && rm -R BrickGame
	make clean

# Build Qt application
qt:
	cd gui/desktop/BrickGame && qmake6 && make && make clean

# Clean up build artifacts
clean:
	rm -rf snake_game tetris_game tests_snake tests_tetris *.gcno *.info *.gcda report *.o *.a
