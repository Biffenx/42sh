/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 14:43:00 by vkuokka          ###   ########.fr       */
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
	size_t				length;
	size_t				x;
	size_t				y;
}						t_editor;

typedef struct	s_shell
{
	int			mode;
	char		**env;
	pid_t		pgid;
	// job control here
	t_terminal	terminal;
	t_editor	editor;
}				t_shell;

int		print_char(int c);
void	signals(t_shell *shell);
void	reset(char *prompt, t_shell *shell);
void	editor(t_shell *shell);
void	action(int key, t_shell *shell);
void	print(t_shell *shell);
int		move_cursor_right_word(t_editor *editor);
int		move_cursor_right(t_editor *editor);
int		move_cursor_left(t_editor *editor);
int		move_cursor_right_word(t_editor *editor);
int		move_cursor_left_word(t_editor *editor);
int		move_cursor_up(t_shell *shell);
int		move_cursor_down(t_shell *shell);
int		handle_eof(t_shell *shell);
int		handle_backspace(t_editor *editor);

#endif
