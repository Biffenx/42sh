/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/07 21:55:16 by vkuokka          ###   ########.fr       */
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
# include <fcntl.h>

# ifndef ARG_MAX
#  define ARG_MAX 2097152
# endif

# define INTERACTIVE 1 << 0
# define INTERRUPT 1 << 1
# define ENDOFFILE 1 << 2
# define READMORE 1 << 3

# define PROMPT_SIZE 9
# define PROMPT_NORMAL ">"
# define PROMPT_QUOTE "quote>"
# define PROMPT_HEREDOC "heredoc>"
# define PROMPT_PIPE "pipe>"

# define HISTORY_SIZE 10
# define HISTORY_FILE ".history"

typedef struct			s_terminal
{
	struct termios		original;
	struct termios		raw;
	struct winsize		size;
}						t_terminal;

typedef struct 			s_editor
{
	char				prompt[PROMPT_SIZE];
	char				buffer[ARG_MAX];
	size_t				cursor;
}						t_editor;

typedef struct	s_shell
{
	int			mode;
	char		**env;
	pid_t		pgid;
	// job control here
	t_terminal	terminal;
	t_editor	editor;
	char		*history[HISTORY_SIZE];
	int			history_index;
}				t_shell;

int		print_char(int c);
void	signals(t_shell *shell);
void	reset(char *prompt, t_shell *shell);
void	add_entry(t_shell *shell);
void	editor(t_shell *shell);
int		keypress(void);
void	action(int key, t_shell *shell);
void	print(t_shell *shell);
int		move_cursor_right_word(t_editor *editor);
int		move_cursor_right(t_editor *editor);
int		move_cursor_left(t_editor *editor);
int		move_cursor_right_word(t_editor *editor);
int		move_cursor_left_word(t_editor *editor);
int		move_cursor_up(t_shell *shell);
int		move_cursor_down(t_shell *shell);
int		browse_up(t_shell *shell);
int		browse_down(t_shell *shell);
void	search_history(t_shell *shell);
int		exclamation(t_shell *shell);
int		handle_eof(t_shell *shell);
int		handle_backspace(t_editor *editor);
void	fetch(t_shell *shell);
void 	save(t_shell *shell);

#endif
