VPATH = ./:../matrix

CXX = g++
CPPFLAGS = -I../matrix
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
LDFLAGS =
LDLIBS =

SRC = network.cpp matrix.cpp test_net.cpp
OBJ = $(SRC:.cpp=.o)

all: test

test: $(OBJ)
	$(LINK.cc) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(OBJ)
	$(RM) test
