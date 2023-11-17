CC = g++
CFLAGS = -std=c++11 -Wall 

SRCS = main.cpp doublelist.h

TARGET = main

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	make run

run: $(TARGET)
	./$(TARGET)

.PHONY: clean

clean:
	rm -f $(TARGET)