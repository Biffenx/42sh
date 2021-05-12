/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:17:19 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/12 16:06:19 by vkuokka          ###   ########.fr       */
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

int		move_cursor_up(t_editor *editor)
{
	int	i;
	char	*buffer;
	int	diff;

	i = editor->cursor;
	buffer = editor->buffer;
	diff = 0;
	if (buffer[i] == '\n')
	{
		i -= 1;
		diff += 1;
	}
	while (i > 0 && buffer[i] != '\n')
	{
		i -= 1;
		diff += 1;
	}
	i -= 1;
	while (i > 0 && buffer[i] != '\n')
		i -= 1;
	editor->cursor = i;
	diff -= 1;
	editor->cursor += 1;
	while (diff && editor->buffer[editor->cursor] != '\n')
	{
		move_cursor_right(editor);
		diff -= 1;
	}
	return (1);
}

int		move_cursor_down(t_editor *editor)
{
	int	i;
	char	*buffer;
	int	diff;

	i = editor->cursor;
	buffer = editor->buffer;
	diff = 0;
	if (buffer[i] == '\n')
	{
		i -= 1;
		diff += 1;
	}
	while (i > 0 && buffer[i] != '\n')
	{
		i -= 1;
		diff += 1;
	}
	i += 1;
	while (i > 0 && buffer[i] != '\n')
		i += 1;
	editor->cursor = i;
	diff -= 1;
	editor->cursor += 1;
	while (diff && editor->buffer[editor->cursor] != '\n')
	{
		move_cursor_right(editor);
		diff -= 1;
	}
	return (1);
}
