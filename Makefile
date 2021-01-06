# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 20:01:25 by vkuokka           #+#    #+#              #
#    Updated: 2021/01/06 11:45:37 by vkuokka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = 42sh

lib = -L libft/ -lft -I libft/
inc = inc/
src = src/main.c \
	src/reset.c \
	src/signals.c \
	src/utils.c \
	src/editor/action.c \
	src/editor/cursor_movement_1.c \
	src/editor/cursor_movement_2.c \
	src/editor/deletion.c \
	src/editor/editor.c \
	src/editor/print.c
flags = -Wall -Wextra -Werror

all:
	gcc $(flags) -I $(inc) $(src) $(lib) -ltermcap -o $(name) 

clean:

fclean:
	rm -f 42sh

re: fclean all
