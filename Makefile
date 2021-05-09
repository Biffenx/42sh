# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 20:01:25 by vkuokka           #+#    #+#              #
#    Updated: 2021/05/09 18:35:58 by vkuokka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = 42sh

lib = -L libft/ -lft -I libft/
inc = -I inc/ -I libft/inc
src = src/main.c \
	src/add_entry.c \
	src/fetch.c \
	src/globl.c \
	src/hashmap.c \
	src/preprocess.c \
	src/reset.c \
	src/save.c \
	src/signals.c \
	src/utils.c \
	src/editor/action.c \
	src/editor/browse_history.c \
	src/editor/clipboard.c \
	src/editor/cursor_movement_1.c \
	src/editor/cursor_movement_2.c \
	src/editor/deletion.c \
	src/editor/editor.c \
	src/editor/exclamation.c \
	src/editor/keypress.c \
	src/editor/parse.c \
	src/editor/print.c \
	src/job/create.c \
	src/job/find_path.c \
	src/job/free_job.c \
	src/job/job_debug.c \
	src/job/tokens_to_array.c \
	src/job/utils.c \
	src/job/utils2.c \
	src/job/utils3.c \
	src/launcher/builtin.c \
	src/launcher/isbuiltin.c \
	src/launcher/job.c \
	src/launcher/process.c \
	src/launcher/builtins/fc/execute.c \
	src/launcher/builtins/fc/fc_debug.c \
	src/launcher/builtins/fc/fc.c \
	src/launcher/builtins/fc/list.c \
	src/launcher/builtins/fc/file.c \
	src/launcher/builtins/fc/parse.c \
	src/launcher/builtins/echo.c \
	src/launcher/builtins/jobs.c \
	src/launcher/builtins/shell_exit.c \
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
	src/redirection/create.c \
	src/redirection/parse.c \
	src/redirection/parse2.c \
	src/redirection/utils.c
flags = -Wall -Wextra -Werror

all:
	-@git clone https://github.com/vkuokka/42-libft.git libft
	@make -C libft
	@gcc $(flags) $(inc) $(src) $(lib) -ltermcap -o $(name) 
simple:
	@echo Skipped libft creation. Launching 42sh ...
	@gcc $(flags) $(inc) $(src) $(lib) -ltermcap -o $(name)
	./42sh
clean:
	make clean -C libft
fclean:
	make fclean -C libft
	rm -f 42sh

re: fclean all
