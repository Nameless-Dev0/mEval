CC = gcc
CFLAGS = -g -fsanitize=address -fno-omit-frame-pointer -O1 -Wall -Werror -Wextra -Iinclude
LDFLAGS = -fsanitize=address

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
HEADER = $(wildcard include/*.h)
TARGET = build/mEval

# Exclude main.c for tests
SRC_NO_MAIN = $(filter-out src/main.c, $(SRC))
OBJ_NO_MAIN = $(patsubst src/%.c, build/%.o, $(SRC_NO_MAIN))

# Test build
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(patsubst tests/%.c, build_tests/%.o, $(TEST_SRC))
TEST_TARGET = build_tests/test_runner

.PHONY: all clean tests

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Tests build
tests: $(TEST_TARGET)

$(TEST_TARGET): $(OBJ_NO_MAIN) $(TEST_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ_NO_MAIN) $(TEST_OBJ) -o $@ $(LDFLAGS)

build_tests/%.o: tests/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/* build_tests/*

-include $(DEP)
