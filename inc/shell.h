/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/02 18:36:50 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "keyboard.h"
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>

# ifdef __linux__
#  include <linux/limits.h>
# else
#  ifdef __APPLE__
#   include <limits.h>
#   include <crt_externs.h>
#   define environ (*_NSGetEnviron ())
#  endif
# endif

# include "errors.h"
# include "autocomplete.h"
# include "builtin.h"

# define INTERACTIVE 		1 << 0
# define INTERRUPT 			1 << 1
# define ENDOFFILE 			1 << 2
# define LOADJOB			1 << 3

# define PROMPT_SIZE 		10
# define PROMPT_NORMAL 		"command> "
# define PROMPT_QUOTE 		"quote> "
# define PROMPT_HEREDOC 	"heredoc> "
# define PROMPT_PIPE 		"pipe> "

# define OUTPUT 			STDOUT_FILENO
# define PASS 				(void)0

typedef struct s_terminal
{
	struct termios	original;
	struct termios	raw;
	struct winsize	size;
}					t_terminal;

typedef struct s_editor
{
	char			prompt[PROMPT_SIZE];
	char			buffer[ARG_MAX];
	size_t			cursor;
	char			clipboard[ARG_MAX];
}							t_editor;

# include "job.h"
# include "hash.h"

# define HISTORY_SIZE 		100
# define HISTORY_FILE 		".42history"

typedef struct s_shell
{
	int				exit;
	char			mode;
	pid_t			pgid;
	t_hash			vars[HASH_SIZE];
	t_hash			alias[HASH_SIZE];
	int				alias_index; // IMO the alias expansion controlling should be the lexers job. What is this needed for?
	t_hash			table[HASH_SIZE];
	t_hash			paths[HASH_SIZE];
	t_job			*jobs;
	t_job			*current;
	t_job			*previous;
	t_terminal		terminal;
	t_editor		editor;
	t_autocomp		*autocomp;
	t_autocomp		*autocomp_tail;
	char			*history[HISTORY_SIZE];
	int				history_index;
	int				prev_key_pressed;
	char			**matching_commands;
}					t_shell;

# include "history.h"
# include "launcher.h"
# include "lexer.h"
# include "parser.h"

extern char		**environ;
extern t_shell	*g_shell;
extern int		g_debug;

/*
** Line edition prototypes.
*/

int		print_char(int c);
void	reset(char *prompt, t_shell *shell);
void	editor(t_shell *shell);
int		keypress(void);
void	action(int key, t_shell *shell);
void	print(t_shell *shell);
int		move_cursor_right_word(t_editor *editor);
int		move_cursor_right(t_editor *editor);
int		move_cursor_left(t_editor *editor);
int		move_cursor_right_word(t_editor *editor);
int		move_cursor_left_word(t_editor *editor);
int		move_cursor_up(t_editor *editor);
int		move_cursor_down(t_editor *editor);
int		check_clipboard_keys(int key, t_shell *shell);
int		handle_eof(t_shell *shell);
int		handle_backspace(t_editor *editor);

void	exit_error(int err, char *msg);
void	preprocess(char *input, t_shell *shell);
void	print_error(int err, char *msg);
void	create_shell(t_shell *shell);
void	signals(void);

void	autocomplete(t_shell *shell);
void	get_autocomplete_commands(t_shell *shell);

extern char		**environ;
extern t_shell	*g_shell;
extern int		g_debug;

#endif
