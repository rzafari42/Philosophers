# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/29 19:29:28 by rzafari           #+#    #+#              #
#    Updated: 2021/04/29 19:29:30 by rzafari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo_one
HEADER = philo_one.h
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
