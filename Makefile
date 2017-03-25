# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 11:23:48 by rbohmert          #+#    #+#              #
#    Updated: 2017/03/17 16:25:07 by rbohmert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, fclean, clean, re

NAME =	21

LIB =	libft/libft.a

SRC =	minishell/minishell.c minishell/builtins.c minishell/utils.c\
		minishell/env.c minishell/setenv.c 21.c lexer.c parser.c resolve.c\
		manage.c\

GCC =	gcc -g -o $(NAME) -I/usr/include/

all: $(NAME)

$(NAME):
		make -C libft/
		$(GCC) $(SRC) $(LIB)

clean:
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
