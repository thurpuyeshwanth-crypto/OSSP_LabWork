CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRC = src/main.c src/input.c src/parser.c src/process.c src/builtin.c src/signals.c
TARGET = bin/shellforge
.PHONY: all run clean
all: $(TARGET)
$(TARGET): $(SRC) include/shell.h include/input.h include/parser.h include/process.h include/builtin.h include/signals.h
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
run: $(TARGET)
	./$(TARGET)
clean:
	rm -rf bin/*
