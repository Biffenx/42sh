/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:17:19 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 14:22:26 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		move_cursor_right_word(t_editor *editor)
{
	while (editor->buffer[editor->cursor] \
	&& ft_isspace(editor->buffer[editor->cursor]))
		move_cursor_right(editor);
	while (editor->buffer[editor->cursor] \
	&& !ft_isspace(editor->buffer[editor->cursor]))
		move_cursor_right(editor);
	return (1);
}

int		move_cursor_left_word(t_editor *editor)
{
	while (editor->cursor > 0 && \
	ft_isspace(editor->buffer[editor->cursor - 1]))
		move_cursor_left(editor);
	while (editor->cursor > 0 && \
	!ft_isspace(editor->buffer[editor->cursor - 1]))
		move_cursor_left(editor);
	return (1);
}

static int	find_newline(t_editor *editor, int *i, int *diff)
{
	if (editor->buffer[*i] == '\n')
	{
		*i -= 1;
		*diff += 1;
	}
	while (*i > 0 && editor->buffer[*i] != '\n')
	{
		*i -= 1;
		*diff += 1;
	}
	return (1);
}

int		move_cursor_up(t_editor *editor)
{
	int	i;
	int	diff;

	i = editor->cursor;
	diff = 0;
	find_newline(editor, &i, &diff);
	if (i == 0)
		return (1);
	i -= 1;
	while (i >= 0 && editor->buffer[i] != '\n')
		i -= 1;
	editor->cursor = i + 1;
	diff -= 1;
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
	int	diff;

	i = editor->cursor;
	diff = 0;
	find_newline(editor, &i, &diff);
	i += 1;
	while (i < (int)ft_strlen(editor->buffer) && editor->buffer[i] != '\n')
		i += 1;
	if (i == (int)ft_strlen(editor->buffer))
		return (1);
	editor->cursor = i + 1;
	diff -= 1;
	while (diff && editor->buffer[editor->cursor] != '\n')
	{
		move_cursor_right(editor);
		diff -= 1;
	}
	return (1);
}
