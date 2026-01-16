SRC=main.c
NAME=nanoshell
FLAGS= -Wall -Wextra
#FLAGS= -Wall -Wextra -Werror
all: $(SRC)
	gcc $(SRC) -o $(NAME) $(FLAGS)
