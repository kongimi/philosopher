# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 14:41:01 by npiyapan          #+#    #+#              #
#    Updated: 2024/03/30 17:15:47 by npiyapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = include/philo.h

OBJ_DIR = bin/
CC = cc
# CFLAGS = -Wall -Werror -Wextra
CFLAGS = -Wall -Werror -Wextra 
# CFLAGS = -fsanitize=thread -g -lpthread
# CFLAGS = -Wno-nullability-completeness


SRC_FILE = philo check_input handle_error utils init_all time monitor_thds

SRC = $($(addsuffix .c, $(SRC_FILE)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILE)))

bin/%.o: %.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf bin
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all bonus clean fclean re
