/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:57:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/05 21:55:18 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
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

#endif