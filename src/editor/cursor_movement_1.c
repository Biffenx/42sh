/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:17:19 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/07 21:58:27 by vkuokka          ###   ########.fr       */
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
	int	result;

	result = shell->editor.cursor - shell->terminal.size.ws_col;
	if (result >= 0)
		shell->editor.cursor = result;
	return (1);
}

int		move_cursor_down(t_shell *shell)
{
	int	result;

	result = shell->editor.cursor + shell->terminal.size.ws_col;
	if (result <= (int)ft_strlen(shell->editor.buffer))
		shell->editor.cursor = result;
	return (1);
}
