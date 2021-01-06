/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:40:34 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 11:18:16 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_char(t_editor *editor, char c)
{
	if (editor->length >= ARG_MAX)
		return ;
	/* if (editor->buffer[editor->cursor->x])
		ft_memmove(editor->buffer + editor->cursor->x + 1, \
		editor->buffer + editor->cursor->x, \
		editor->len + editor->cursor->x); */
	editor->buffer[editor->x] = c;
	editor->length++;
	editor->x++;
}

void		action(int key, t_shell *shell)
{
	if (ft_isprint(key))
		add_char(&shell->editor, (char)key);
	/* else if (key == CTRL_R)
		browse(shell, key); */
	else if (key == CTRL_L)
		tputs(tgetstr("cl", NULL), 1, print_char);
	else if (key == TAB)
	{
		/* if (!shell->mode & READMORE)
			autocomplete(shell); */
	}
	else if (key == ESC) // This condition will be deleted in final product.
		exit(1);
	/* else if (check_arrow_keys(key, shell))
		return ;
	else if (check_clipboard_keys(key, shell))
		return ;
	else if (check_delete_keys(key, shell))
		return ;
	else if (check_leap_keys(key, shell))
		return ; */
}
