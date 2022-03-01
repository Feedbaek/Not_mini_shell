# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:50:35 by minskim2          #+#    #+#              #
#    Updated: 2022/02/27 16:38:48 by minskim2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Werror -Wextra -Wall
SRCS = srcs/main.c \
		srcs/prompts/prompt.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_cd.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_exit.c \
		srcs/pipex/pipex.c \
		srcs/pipex/path_finder.c \
		srcs/pipex/pipex_split.c \
		srcs/pipex/pipex_strjoin.c \
		srcs/pipex/redirect.c \
		srcs/pipex/utils.c \
		srcs/utils/cpy_env.c

TEST_SRCS = \
		srcs/pipex/path_finder.c \
		srcs/pipex/pipex_split.c \
		srcs/pipex/pipex_strjoin.c \
		srcs/pipex/redirect.c \
		srcs/pipex/utils.c \
		srcs/pipex/test.c

SRCS_BONUS =

HEADER = $(shell pwd)/include
OBJECTS = $(SRCS:.c=.o)
OBJECTS_TEST = $(TEST_SRCS:.c=.o)
OBJECTS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT_LDIR	= $(shell pwd)/Libft
FT_LIBFT 	= $(LIBFT_LDIR)/libft.a
LIBFT_NAME	= ft
LIBFT_LIB	= -L$(LIBFT_LDIR) -l$(LIBFT_NAME)

ifdef WITH_BONUS
	NAME = minishell_bonus
	OBJS = $(OBJECTS_BONUS)
else
	ifdef WITH_TEST
		NAME = minishell_test
		OBJS = $(OBJECTS_TEST)
	else
		NAME = minishell
		OBJS = $(OBJECTS)
	endif
endif

all: $(NAME)

test:
	make WITH_TEST=1 all

bonus:
	make WITH_BONUS=1 all

.PHONY: all clean fclean re bonus test

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I$(HEADER)

$(FT_LIBFT):
	make -C $(LIBFT_LDIR)

$(NAME): $(FT_LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline $(LIBFT_LIB)

clean:
	make -C $(LIBFT_LDIR) clean
	rm -rf $(OBJECTS) $(OBJECTS_BONUS) $(OBJECTS_TEST)

fclean: clean
	make -C $(LIBFT_LDIR) fclean
	rm -rf minishell minishell_bonus minishell_test

re: fclean all
