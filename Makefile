##
## EPITECH PROJECT, 2025
## nanotekspice
## Makefile
##

NAME        = nanotekspice
TEST_NAME   = unit_tests

CXX         = clang++

INCLUDES = \
    -Iinclude \
    -Iinclude/Components \
    -Iinclude/Components/Core \
    -Iinclude/Components/Exception \
    -Iinclude/Components/Operators \
    -Iinclude/Components/Factory \
    -Iinclude/Components/IO \
    -Iinclude/Components/Chipset \
    -Iinclude/Parser \
    -Iinclude/Circuit \
    -Itests

BASE_FLAGS  = -Wall -Wextra -std=c++20
CXXFLAGS    = $(BASE_FLAGS) $(INCLUDES)
LDLIBS      = -lcriterion

SRC             = $(shell find src -name '*.cpp')
SRC_NO_MAIN     = $(filter-out src/Main.cpp, $(SRC))
TEST_SRC        = $(shell find tests -name '*.cpp')

OBJ             = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(TEST_NAME):
	$(CXX) ${CXXFLAGS} $(SRC_NO_MAIN) $(TEST_SRC) -o $@ $(LDFLAGS) --coverage $(LDLIBS)

tests_run: $(TEST_NAME)
	./$<

clean:
	rm -rf $(OBJ) $(TEST_OBJ)
	find . -type f -name "*.gcda" -delete
	find . -type f -name "*.gcno" -delete
	find . -type f -name "*.gcov" -delete

fclean: clean
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all
