/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:57:51 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/09 12:11:08 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	cursor(t_shell *shell)
{
	size_t	cursor;
	size_t	row_len;

	tputs(tgetstr("rc", NULL), 1, print_char);
	cursor = 0;
	row_len = 0;
	while (cursor < ft_strlen(shell->editor.prompt))
	{
		tputs(tgetstr("nd", NULL), 1, print_char);
		cursor += 1;
	}
	cursor = 0;
	row_len = ft_strlen(shell->editor.prompt);
	while (cursor < shell->editor.cursor)
	{
		tputs(tgetstr("nd", NULL), 1, print_char);
		cursor += 1;
		row_len +=1;
		if (row_len == shell->terminal.size.ws_col)
			write(STDOUT_FILENO, "\n\r", 2);
		else if (shell->editor.buffer[cursor - 1] == '\n')
			write(STDOUT_FILENO, "\n\r", 2);
		else
			continue ;
		row_len = 0;
	}
}

void		print(t_shell *shell)
{
	tputs(tgetstr("rc", NULL), 1, print_char);
	tputs(tgetstr("cd", NULL), 1, print_char);
	ft_putstr(shell->editor.prompt);
	ft_putstr(shell->editor.buffer);
	cursor(shell);
}
