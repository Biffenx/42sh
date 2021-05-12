/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:17:19 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/12 08:54:46 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_cursor_right_word(t_editor *editor)
{
	while (editor->buffer[editor->cursor] \
	&& editor->buffer[editor->cursor] == ' ')
		move_cursor_right(editor);
	while (editor->buffer[editor->cursor] \
	&& editor->buffer[editor->cursor] != ' ')
		move_cursor_right(editor);
	return (1);
}

int		move_cursor_left_word(t_editor *editor)
{
	while (editor->cursor > 0 && \
	editor->buffer[editor->cursor - 1] == ' ')
		move_cursor_left(editor);
	while (editor->cursor > 0 && \
	editor->buffer[editor->cursor - 1] != ' ')
		move_cursor_left(editor);
	return (1);
}

int		move_cursor_up(t_shell *shell)
{
	if (!shell)
		exit (1);
	return (1);
}

int		move_cursor_down(t_shell *shell)
{
	if (!shell)
		exit (1);
	return (1);
}
