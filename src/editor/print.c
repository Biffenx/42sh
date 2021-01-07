/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:57:51 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/07 21:59:28 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	cursor(t_shell *shell)
{
	size_t	cursor;

	tputs(tgetstr("rc", NULL), 1, print_char);
	cursor = 0;
	while (cursor < ft_strlen(shell->editor.prompt) + shell->editor.cursor)
	{
		tputs(tgetstr("nd", NULL), 1, print_char);
		cursor++;
		if (cursor % shell->terminal.size.ws_col == 0)
			tputs(tgetstr("do", NULL), 1, print_char);
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
