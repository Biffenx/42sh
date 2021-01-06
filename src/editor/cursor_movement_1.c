/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:17:19 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 11:36:05 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_cursor_right_word(t_editor *editor)
{
	while (editor->buffer[editor->x] \
	&& editor->buffer[editor->x] == ' ')
		move_cursor_right(editor);
	while (editor->buffer[editor->x] \
	&& editor->buffer[editor->x] != ' ')
		move_cursor_right(editor);
	return (1);
}

int		move_cursor_left_word(t_editor *editor)
{
	while (editor->x > 0 && \
	editor->buffer[editor->x - 1] == ' ')
		move_cursor_left(editor);
	while (editor->x > 0 && \
	editor->buffer[editor->x - 1] != ' ')
		move_cursor_left(editor);
	return (1);
}

int		move_cursor_up(t_shell *shell)
{
	int	result;

	result = shell->editor.x - shell->terminal.size.ws_col;
	if (result >= 0)
		shell->editor.x = result;
	return (1);
}

int		move_cursor_down(t_shell *shell)
{
	int	result;

	result = shell->editor.x + shell->terminal.size.ws_col;
	if (result <= (int)shell->editor.length)
		shell->editor.x = result;
	return (1);
}
