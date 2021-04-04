
NAME = philo_three
HEADER = philo_three.h
CC = gcc
CLFAGS = -Wall -Wextra -Werror -lpthread
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):  $(OBJ)
		$(CC) $(CLFAGS) -I $(HEADER) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
