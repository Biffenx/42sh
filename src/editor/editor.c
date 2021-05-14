/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:03:50 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/14 12:35:30 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	terminal_mode(int reset, t_terminal *terminal)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &terminal->size);
	if (reset)
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal->original);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal->raw);
}

static void	input(t_shell *shell)
{
	size_t	key;

	tputs(tgetstr("sc", NULL), 1, print_char);
	while (1)
	{
		print(shell);
		key = keypress();
		action(key, shell);
		if (shell->mode & ENDOFFILE || shell->mode & INTERRUPT || key == ENTER)
		{
			write(1, "\n", 1);
			break ;
		}
	}
}

static void	loop(t_shell *shell)
{
	while (1)
	{
		input(shell);
		if (shell->mode & ENDOFFILE || shell->mode & INTERRUPT)
			break ;
		else if (exclamation(shell))
			continue ;
		else
			break ;
	}
}

void		editor(t_shell *shell)
{
	char	*line;

	if (~shell->mode & INTERACTIVE)
	{
		if (!get_next_line(0, &line))
		{
			shell->mode = shell->mode | ENDOFFILE;
			return ;
		}
		if (ft_strlen(line) < ARG_MAX)
			ft_strcat(shell->editor.buffer, line);
		free(line);
	}
	else
	{
		terminal_mode(0, &shell->terminal);
		loop(shell);
		terminal_mode(1, &shell->terminal);
	}
}
