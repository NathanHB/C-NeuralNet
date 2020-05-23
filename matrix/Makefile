CXX = g++
CPPFLAGS =
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
LDFLAGS =
LDLIBS =

SRC = matrix.cpp test_matrix.cpp
OBJ = $(SRC:.cpp=.o)

all: test

test: $(OBJ)
	$(LINK.cc) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(OBJ)
	$(RM) test
