# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:50:35 by minskim2          #+#    #+#              #
#    Updated: 2022/01/06 16:10:31 by minskim2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Werror -Wextra -Wall
SRCS = srcs/main.c

SRCS_BONUS =

LIBFT_LDIR	= $(shell pwd)/Libft
FT_LIBFT 	= $(LIBFT_LDIR)/libft.a
LIBFT_NAME	= ft
LIBFT_LIB	= -L$(LIBFT_LDIR) -l$(LIBFT_NAME)

HEADER = include
OBJECTS = $(SRCS:.c = .o)
OBJECTS_BONUS = $(SRCS_BONUS:.c = .o)

ifdef WITH_BONUS
	NAME = minishell_bonus
	OBJS = $(OBJECTS_BONUS)
else
	NAME = minishell
	OBJS = $(OBJECTS)
endif

.PHONY: all clean fclean re bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(HEADER) $(LIBFT_LIB)

all: $(NAME)

$(FT_LIBFT):
	make -C $(LIBFT_LDIR)

$(NAME): $(OBJS) $(FT_LIBFT)
	$(CC) $(CFLAGS) $^ -o $@

bonus:
	make WITH_BONUS=1 all

clean:
	make -C $(LIBFT_LDIR) clean
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean:
	make -C $(LIBFT_LDIR) fclean
	rm -rf minishell minishell_bonus $(OBJECTS) $(OBJECTS_BONUS)

re: fclean all
