/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/02/24 19:00:29 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "keyboard.h"
# include "hash.h"
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>

# ifndef ARG_MAX
#  define ARG_MAX 			2097152
# endif

# define INTERACTIVE 		1 << 0
# define INTERRUPT 			1 << 1
# define ENDOFFILE 			1 << 2

# define PROMPT_SIZE 		9
# define PROMPT_NORMAL 		">"
# define PROMPT_QUOTE 		"quote>"
# define PROMPT_HEREDOC 	"heredoc>"
# define PROMPT_PIPE 		"pipe>"

# define HISTORY_SIZE 		10
# define HISTORY_FILE 		".history"

# define OUTPUT 			STDOUT_FILENO
# define PASS 				(void)0

/*
** Error numbers
*/

# define MALLOC_ERROR		2
# define FORK_ERR			3
# define EXECVE_ERROR		4
# define SYNTAX_ERR			5
# define PERMISSION_ERR 	6
# define NOT_FOUND_ERR		7
# define NOT_DIR_ERR		8
# define PIPE_ERR			9
# define DUP_ERR			10
# define REDIR_ERR			11
# define AMB_REDIR_ERR		12
# define EOF_ERR			14
# define HEREDOC_ERR		15
# define BAD_FD_ERR			16

/*
** Error messages
*/

# define STR_MALLOC_ERR		"42sh: malloc error."
# define STR_FORK_ERR 		"42sh: failed to create child process."
# define STR_EXECVE_ERR		"42sh: execve error."
# define STR_SYNTAX_ERR		"42sh: syntax error near unexpected token"
# define STR_PERMISSION_ERR	"42sh: permission denied:"
# define STR_NOT_FOUND_ERR	"42sh: No such file or directory"
# define STR_NOT_DIR_ERR	"42sh: Not a directory"
# define STR_IS_DIR			"42sh: is a directory:"
# define STR_PIPE_ERR		"42sh: pipe error"
# define STR_DUP_ERR		"42sh: dup error."
# define STR_REDIR_ERR		"42sh: redirection error."
# define STR_AMB_REDIR_ERR	"42sh: ambiguous redirection:"
# define STR_EOF_ERR		"42sh: unexpected EOF while looking for matching"
# define STR_HERE_ERR		"42sh: warning: here-document delimited by end-of-file"
# define STR_BAD_FD_ERR		"42sh: Bad file descriptor:"

typedef struct				s_terminal
{
	struct termios			original;
	struct termios			raw;
	struct winsize			size;
}							t_terminal;

typedef struct 				s_editor
{
	char					prompt[PROMPT_SIZE];
	char					buffer[ARG_MAX];
	size_t					cursor;
}							t_editor;

typedef struct				s_shell
{
	int						status;
	int						mode;
	char					**env;
	pid_t					pgid;
	// job control here
	t_terminal				terminal;
	t_editor				editor;
	char					*history[HISTORY_SIZE];
	int						history_index;
	t_dict					*dict[HASH_SIZE];
}							t_shell;

# include "lexer.h"
# include "parser.h"

extern t_shell *g_shell;

void						hash_insert(int key, char **data, t_shell *shell);
t_dict						*hash_search(int key, t_shell *shell);
int							array_display(int hashkey);
int							array_find(int hashkey, char *var);
void						array_set(int hashkey, char *key, char *val);
void						array_delete(int hashkey, int pos);
char						*array_get(int hashkey, char *var);
char						**array_realloc(char **arr, size_t size);

int							print_char(int c);
void						signals(t_shell *shell);
void						reset(char *prompt, t_shell *shell);
void						add_entry(t_shell *shell);
void						editor(t_shell *shell);
int							keypress(void);
void						action(int key, t_shell *shell);
void						print(t_shell *shell);
int							move_cursor_right_word(t_editor *editor);
int							move_cursor_right(t_editor *editor);
int							move_cursor_left(t_editor *editor);
int							move_cursor_right_word(t_editor *editor);
int							move_cursor_left_word(t_editor *editor);
int							move_cursor_up(t_shell *shell);
int							move_cursor_down(t_shell *shell);
int							browse_up(t_shell *shell);
int							browse_down(t_shell *shell);
void						search_history(t_shell *shell);
int							exclamation(t_shell *shell);
size_t						parse(t_shell *shell, size_t i, char *tmp);
int							handle_eof(t_shell *shell);
int							handle_backspace(t_editor *editor);
void						fetch(t_shell *shell);
void 						save(t_shell *shell);
void						exit_error(int err, char *msg);
void						preprocess(char *input, t_shell *shell);
void						print_error(int err, char *msg);
void						create_shell(char **env, t_shell *shell);

#endif
