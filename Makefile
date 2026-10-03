CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRC = src/main.c src/input.c src/parser.c
TARGET = bin/shellforge

.PHONY: all run clean
all: $(TARGET)

$(TARGET): $(SRC) include/shell.h include/input.h include/parser.h
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf bin/*
