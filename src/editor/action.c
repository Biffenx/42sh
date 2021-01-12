/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:40:34 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/12 20:04:16 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_char(t_editor *editor, char c)
{
	if (ft_strlen(editor->buffer) >= ARG_MAX)
		return ;
	if (editor->buffer[editor->cursor])
		ft_memmove(editor->buffer + editor->cursor + 1, \
		editor->buffer + editor->cursor, \
		ft_strlen(editor->buffer) + editor->cursor);
	editor->buffer[editor->cursor] = c;
	editor->cursor++;
}

static int	check_arrow_keys(int key, t_shell *shell)
{
	if (key == LEFT)
		return (move_cursor_left(&shell->editor));
	else if (key == RIGHT)
		return (move_cursor_right(&shell->editor));
	else if (key == UP)
		return (browse_up(shell));
	else if (key == DOWN)
		return (browse_down(shell));
	return (0);
}

static int	check_delete_keys(int key, t_shell *shell)
{
	if (key == BACKSPACE)
		return (handle_backspace(&shell->editor));
	else if (key == CTRL_D)
		return (handle_eof(shell));
	return (0);
}

static int	check_leap_keys(int key, t_shell *shell)
{
	if (key == CTRL_LEFT)
		return (move_cursor_left_word(&shell->editor));
	else if (key == CTRL_RIGHT)
		return (move_cursor_right_word(&shell->editor));
	else if (key == CTRL_UP)
		return (move_cursor_up(shell));
	else if (key == CTRL_DOWN)
		return (move_cursor_down(shell));
	else if (key == HOME)
	{
		shell->editor.cursor = 0;
		return (1);
	}
	else if (key == END)
	{
		shell->editor.cursor = ft_strlen(shell->editor.buffer);
		return (1);
	}
	return (0);
}

void		action(int key, t_shell *shell)
{
	if (ft_isprint(key))
		add_char(&shell->editor, (char)key);
	else if (key == CTRL_R)
		search_history(shell);
	else if (key == CTRL_L)
		tputs(tgetstr("cl", NULL), 1, print_char);
	/* else if (key == TAB)
			autocomplete(shell); */
	else if (check_arrow_keys(key, shell))
		return ;
	/* else if (check_clipboard_keys(key, shell))
		return ; */
	else if (check_delete_keys(key, shell))
		return ;
	else if (check_leap_keys(key, shell))
		return ;
}
