# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 15:50:35 by minskim2          #+#    #+#              #
#    Updated: 2022/02/24 17:35:35 by minskim2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Werror -Wextra -Wall
SRCS = srcs/main.c \
		srcs/prompts/prompt.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_cd.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_exit.c \
		srcs/pipex/pipex.c \
		srcs/pipex/path_finder.c \
		srcs/pipex/pipex_split.c \
		srcs/pipex/pipex_strjoin.c \
		srcs/pipex/redirect.c \
		srcs/pipex/utils.c

SRCS_BONUS =

HEADER = $(shell pwd)/include
OBJECTS = $(SRCS:.c=.o)
OBJECTS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT_LDIR	= $(shell pwd)/Libft
FT_LIBFT 	= $(LIBFT_LDIR)/libft.a
LIBFT_NAME	= ft
LIBFT_LIB	= -L$(LIBFT_LDIR) -l$(LIBFT_NAME)

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

$(FT_LIBFT):
	make -C $(LIBFT_LDIR)

$(NAME): $(FT_LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline $(LIBFT_LIB)

bonus:
	make WITH_BONUS=1 all

clean:
	make -C $(LIBFT_LDIR) clean
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	make -C $(LIBFT_LDIR) fclean
	rm -rf minishell minishell_bonus

re: fclean all

debug:
	$(CC) -g $(CFLAGS) $(SRCS) -o minishell -I$(HEADER) -lreadline
