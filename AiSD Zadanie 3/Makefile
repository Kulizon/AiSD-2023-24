CC = g++
CFLAGS = -Wall

SRCS = main.cpp arraylist.h

# Output executable name
TARGET = main

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
	make run

run: $(TARGET)
	./$(TARGET)

.PHONY: clean

clean:
	rm -f $(TARGET)