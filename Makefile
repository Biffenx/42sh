# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 20:01:25 by vkuokka           #+#    #+#              #
#    Updated: 2021/07/30 12:55:05 by vkuokka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = 42sh

lib = -L libft/ -lft -I libft/
inc = -I inc/ -I libft/inc
src = src/main.c \
	src/add_entry.c \
	src/fetch.c \
	src/globl.c \
	src/hash.c \
	src/preprocess.c \
	src/reset.c \
	src/save.c \
	src/signals.c \
	src/utils.c \
	src/utils2.c \
	src/autocomplete/autocomplete.c \
	src/autocomplete/get_autocomplete_commands.c \
	src/editor/action.c \
	src/editor/browse_history.c \
	src/editor/clipboard.c \
	src/editor/cursor_movement_1.c \
	src/editor/cursor_movement_2.c \
	src/editor/deletion.c \
	src/editor/editor.c \
	src/editor/keypress.c \
	src/editor/print.c \
	src/job/create_utils.c \
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
	src/launcher/utils.c \
	src/launcher/builtins/fc/fc_debug.c \
	src/launcher/builtins/fc/fc.c \
	src/launcher/builtins/test/check_values.c \
	src/launcher/builtins/test/flag_bcdef.c\
	src/launcher/builtins/test/flag_binary_sym.c \
	src/launcher/builtins/test/flag_binary_util.c \
	src/launcher/builtins/test/flag_binary.c \
	src/launcher/builtins/test/flag_glprs.c\
	src/launcher/builtins/test/flag_suwxz.c\
	src/launcher/builtins/test/get_options.c\
	src/launcher/builtins/test/util.c\
	src/launcher/builtins/alias.c \
	src/launcher/builtins/bg.c \
	src/launcher/builtins/cd.c \
	src/launcher/builtins/echo.c \
	src/launcher/builtins/exit.c \
	src/launcher/builtins/export.c \
	src/launcher/builtins/fg.c \
	src/launcher/builtins/hash.c \
	src/launcher/builtins/map.c \
	src/launcher/builtins/jobs_utils.c \
	src/launcher/builtins/jobs.c \
	src/launcher/builtins/set.c \
	src/launcher/builtins/test.c \
	src/launcher/builtins/type.c \
	src/launcher/builtins/unalias.c \
	src/launcher/builtins/unset.c \
	src/lexer/debug.c \
	src/lexer/index.c \
	src/lexer/token_control.c \
	src/lexer/token_new.c \
	src/lexer/token_string.c \
	src/lexer/utils.c \
	src/parser/expand_alias.c \
	src/parser/expand_exclamation.c \
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
noflags:
	@echo Skipped libft creation and compiled with no flags. Launching 42sh ...
	@gcc $(inc) $(src) $(lib) -ltermcap -o $(name)
	./42sh
debug:
	@echo Skipped libft creation. Launching 42sh debug mode...
	@gcc $(flags) $(inc) $(src) $(lib) -ltermcap -o $(name)
	./42sh --debug
clean:
	make clean -C libft
fclean:
	make fclean -C libft
	rm -f 42sh

re: fclean all
