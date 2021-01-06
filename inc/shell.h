/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 10:59:23 by vkuokka          ###   ########.fr       */
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

typedef struct			s_terminal
{
	struct termios		original;
	struct termios		raw;
	struct winsize		size;
}						t_terminal;

typedef struct 			s_editor
{
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
void	print(t_editor editor);

#endif
