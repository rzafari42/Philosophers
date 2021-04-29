
NAME = philo_two
HEADER = philo_two.h
CC = gcc
CLFAGS = -Wall -Wextra -Werror -pthread
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

.c.o:
		$(CC) $(CLFAGS) -c $< -o $@
$(NAME):  $(OBJ)
		@$(CC) $(CLFAGS) $(OBJ) -I $(HEADER) -o $(NAME)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
