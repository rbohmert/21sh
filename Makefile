# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 11:23:48 by rbohmert          #+#    #+#              #
#    Updated: 2017/03/29 17:32:23 by rbohmert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, fclean, clean, re

NAME =	21

LIB =	libft/libft.a

SRC =	minishell/minishell.c minishell/builtins.c minishell/utils.c\
		minishell/env.c minishell/setenv.c 21.c line_edit/get_line_tcap.c\
		line_edit/app_key.c line_edit/utils.c line_edit/term_sig.c\
		line_edit/copypaste.c line_edit/key_actions.c\
		history/history.c history/utils.c\
		lexer.c parser.c resolve.c manage.c utils.c exec_redir.c sig.c\

GCC =	gcc -W -Wall -Werror -g -o $(NAME) -I/usr/include/

all: $(NAME)

$(NAME):
		make -C libft/
		make -C libft/ clean
		$(GCC) $(SRC) $(LIB) -ltermcap 

clean:
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
