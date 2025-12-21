CC = gcc
CFLAGS = -g -fsanitize=address -fno-omit-frame-pointer -O1 -Wall -Werror -Wextra -Iinclude
CFLAGS_B = -g -O0 -Wall -Wextra -Iinclude
LDFLAGS = -lm -fsanitize=address

SRC = $(wildcard src/*.c)
SRC_NO_MAIN = $(filter-out src/main.c, $(SRC))
HEADER = $(wildcard include/*.h)

OBJ = $(patsubst src/%.c, build/default/bin/%.o, $(SRC))
TARGET = build/default/mEval

TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(patsubst tests/%.c, build/tests/bin/%.o, $(TEST_SRC))
TEST_SRC_NO_MAIN = $(filter-out src/main.c, $(SRC))
TEST_CORE_OBJ = $(patsubst src/%.c, build/tests/bin/%.o, $(TEST_SRC_NO_MAIN))
TEST_TARGET = build/tests/test_runner

BENCHMARK_SRC = $(wildcard benchmarks/*.c)
BENCHMARK_CORE_OBJ = $(patsubst src/%.c, build/benchmarks/bin/%.o, $(SRC_NO_MAIN))
BENCHMARK_OBJ = $(patsubst benchmarks/%.c, build/benchmarks/bin/%.o, $(BENCHMARK_SRC))
BENCHMARK_TARGET = build/benchmarks/benchmarks

.PHONY: all clean tests benchmarks


all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/default/bin/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_CORE_OBJ) $(TEST_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TEST_CORE_OBJ) $(TEST_OBJ) -o $@ $(LDFLAGS)

build/tests/bin/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/tests/bin/%.o: tests/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


benchmarks: $(BENCHMARK_TARGET)

$(BENCHMARK_TARGET): $(BENCHMARK_CORE_OBJ) $(BENCHMARK_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_B) $(BENCHMARK_CORE_OBJ) $(BENCHMARK_OBJ) -o $@ $(LDFLAGS)

build/benchmarks/bin/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_B) -c $< -o $@

build/benchmarks/bin/%.o: benchmarks/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_B) -c $< -o $@

clean:
	rm -rf build/*
