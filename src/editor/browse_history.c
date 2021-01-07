/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:09:10 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/07 22:02:49 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	find_match(t_shell *shell, char *str)
{
	size_t	i;

	if (!str[0])
		return (1);
	i = 0;
	while (i < HISTORY_SIZE)
	{
		if (ft_strstr(shell->history[i], str))
		{
			reset(NULL, shell);
			ft_strcat(shell->editor.buffer, shell->history[i]);
			shell->editor.cursor = ft_strlen(shell->editor.buffer);
			return (1);
		}
		i++;
	}
	return (0);
}

void		search_history(t_shell *shell)
{
	char	str[ARG_MAX];
	int		key;

	ft_bzero(str, ARG_MAX);
	tputs(tgetstr("cr", NULL), 1, print_char);
	tputs(tgetstr("sc", NULL), 1, print_char);
	while (1)
	{
		find_match(shell, str) ? ft_printf("(reverse-i-search)`%s': ", str)
		: ft_printf("(failed reverse-i-search)`%s': ", str);
		ft_putstr(shell->editor.buffer);
		key = keypress();
		tputs(tgetstr("rc", NULL), 1, print_char);
		tputs(tgetstr("cd", NULL), 1, print_char);
		if (shell->mode & INTERRUPT)
			break ;
		if (key == BACKSPACE && str[0])
			str[ft_strlen(str) - 1] = '\0';
		else if (ft_isprint(key) && ft_strlen(str) < ARG_MAX)
			str[ft_strlen(str)] = key;
		else if (!ft_isprint(key) && key != BACKSPACE)
			break ;
	}
}
int			browse_up(t_shell *shell)
{
	if (shell->history_index < HISTORY_SIZE - 1)
	{
		if (shell->history[shell->history_index + 1])
		{
			shell->history_index++;
			ft_bzero(shell->editor.buffer, ARG_MAX);
			ft_strcat(shell->editor.buffer, shell->history[shell->history_index]);
			shell->editor.cursor= ft_strlen(shell->editor.buffer);
		}
	}
	return (1);
}

int			browse_down(t_shell *shell)
{
	if (shell->history_index > 0)
	{
		if (shell->history[shell->history_index - 1])
		{
			shell->history_index--;
			ft_bzero(shell->editor.buffer, ARG_MAX);
			ft_strcat(shell->editor.buffer, shell->history[shell->history_index]);
			shell->editor.cursor = ft_strlen(shell->editor.buffer);
		}
	}
	return (1);
}
