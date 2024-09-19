CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TESTFLAGS = -lgtest -lsubunit -pthread

TEST_DIR = $(wildcard ./tests/*.cpp)
TEST_OBJ = $(TEST_DIR:.cpp=.o)

ALL_SRC = $(wildcard *.cpp */*.cpp */*/*.cpp *.h */*.h */*/*.h)

.PHONY: test clean clang cppcheck valgrind

test: clean $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test $(TESTFLAGS)
	rm -f $(TEST_OBJ)
	./test

clean:
	rm -f  $(TEST_OBJ) ./test

clang:
	cp ./../materials/linters/.clang-format ./
	clang-format -i $(ALL_SRC)
	rm -f .clang-format

cppcheck:
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem $(ALL_SRC)

valgrind:
	CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./test
