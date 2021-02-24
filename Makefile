# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vesa <vesa@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 20:01:25 by vkuokka           #+#    #+#              #
#    Updated: 2021/02/24 15:00:31 by vesa             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = 42sh

lib = -L libft/ -lft -I libft/
inc = -I inc/ -I libft/inc
src = src/main.c \
	src/add_entry.c \
	src/fetch.c \
	src/hash.c \
	src/preprocess.c \
	src/reset.c \
	src/save.c \
	src/signals.c \
	src/utils.c \
	src/editor/action.c \
	src/editor/browse_history.c \
	src/editor/cursor_movement_1.c \
	src/editor/cursor_movement_2.c \
	src/editor/deletion.c \
	src/editor/editor.c \
	src/editor/exclamation.c \
	src/editor/keypress.c \
	src/editor/parse.c \
	src/editor/print.c \
	src/lexer/debug.c \
	src/lexer/index.c \
	src/lexer/token_control.c \
	src/lexer/token_new.c \
	src/lexer/token_string.c \
	src/lexer/utils.c \
	src/parser/expand_alias.c \
	src/parser/expand.c \
	src/parser/index.c \
	src/parser/syntax.c \
	src/parser/utils.c \
	src/parser/heredoc.c \
	src/parser/quotes.c
flags = -Wall -Wextra -Werror

all:
	gcc $(flags) $(inc) $(src) $(lib) -ltermcap -o $(name) 

clean:

fclean:
	rm -f 42sh

re: fclean all
