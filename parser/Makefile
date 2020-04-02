
CXX = g++
CPPFLAGS =
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
LDFLAGS =
LDLIBS =

SRC = parser.cpp idx_header.cpp
OBJ = $(SRC:.cpp=.o)

all: parser

parser: $(OBJ)
	$(LINK.cc) $^ $(LDLIBS) -o $@

clean:
	${RM} ${OBJ}
	${RM} parser
