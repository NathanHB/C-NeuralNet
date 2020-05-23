VPATH = ./:matrix:parser:network

CXX = g++
CPPFLAGS = -Iparser -Imatrix -Inetwork
CXXFLAGS = -g -Wall -Wextra -std=c++17
LDFLAGS =
LDLIBS =

SRC = network.cpp matrix.cpp idx_header.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all: main

main: $(OBJ)
	$(LINK.cc) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(OBJ)
	$(RM) main
