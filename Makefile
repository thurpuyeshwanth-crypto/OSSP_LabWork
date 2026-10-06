CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -Iinclude
SRC = src/main.c src/input.c src/parser.c src/process.c src/builtin.c src/signals.c src/pipes.c src/redirect.c
TARGET = bin/shellforge
.PHONY: all run clean asan valgrind test
all: $(TARGET)
$(TARGET): $(SRC) $(wildcard include/*.h)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
run: $(TARGET)
	./$(TARGET)
asan:
	mkdir -p bin
	$(CC) $(CFLAGS) -fsanitize=address -fno-omit-frame-pointer $(SRC) -o bin/shellforge_asan
valgrind: $(TARGET)
	printf 'pwd\necho memory-check\nexit\n' | valgrind --leak-check=full --error-exitcode=9 ./$(TARGET)
test: $(TARGET)
	sh ./tests/smoke.sh ./$(TARGET)
clean:
	rm -rf bin/* tests/*.tmp
