CC = g++
CFLAGS = -std=c++11 -Wall
SDL_FLAGS = -lSDL2

SRCS = Main.cpp Maze.cpp
HEADERS = Maze.h

TARGET = main

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(SDL_FLAGS)
	make run

run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
