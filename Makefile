NAME		=	raytracer

SRC			=	$(shell find src -name '*.cpp')
OBJ			=	$(SRC:.cpp=.o)

CXX			?=	g++
CXXFLAGS	+=	-std=c++20 -O3 -Wall -Wextra -Iinclude
LDLIBS		=	-lconfig++ -lz -pthread

ifeq ($(shell uname),Darwin)
	BREW		:=	$(shell brew --prefix 2>/dev/null)
	CXXFLAGS	+=	-I$(BREW)/include
	LDFLAGS		+=	-L$(BREW)/lib
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
