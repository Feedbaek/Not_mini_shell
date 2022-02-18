# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungmcho <sungmcho@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:50:35 by minskim2          #+#    #+#              #
#    Updated: 2022/02/18 10:40:03 by sungmcho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Werror -Wextra -Wall
SRCS = srcs/main.c

SRCS_BONUS =

HEADER = include
OBJECTS = $(SRCS:.c=.o)
OBJECTS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	NAME = minishell_bonus
	OBJS = $(OBJECTS_BONUS)
else
	NAME = minishell
	OBJS = $(OBJECTS)
endif

.PHONY: all clean fclean re bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(HEADER)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bonus:
	make WITH_BONUS=1 all

clean:
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -rf minishell minishell_bonus

re: fclean all
