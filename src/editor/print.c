/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:57:51 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 11:53:48 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	cursor(t_editor editor)
{
	size_t	cursor;

	tputs(tgetstr("rc", NULL), 1, print_char);
	cursor = 0;
	while (cursor < editor.x)
	{
		tputs(tgetstr("nd", NULL), 1, print_char);
		cursor++;
	}
}

void		print(t_editor editor)
{
	tputs(tgetstr("rc", NULL), 1, print_char);
	tputs(tgetstr("cd", NULL), 1, print_char);
	ft_putstr(editor.buffer);
	cursor(editor);
}
