##
## EPITECH PROJECT, 2023
## undefined
## File description:
## Makefile
##

SRC =   $(wildcard ./src/*.cpp) \
		$(wildcard ./src/**/*.cpp) \

CFLAGS	=	-std=gnu++2a -W -Wall -iquote. -Wextra -Ofast -lsfml-graphics -lsfml-window -lsfml-system

OBJ =	$(SRC:.cpp=.o)

NAME	=	raytracer

all:		$(OBJ) $(NAME)
	g++ -g -o $(NAME) $(OBJ) $(CFLAGS)

$(NAME):	all

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
