/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:28:57 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/07 21:59:01 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			handle_eof(t_shell *shell)
{
	size_t	len;

	if (!shell->editor.buffer[0])
		shell->mode = shell->mode | ENDOFFILE;
	else if (shell->editor.buffer[shell->editor.cursor])
	{
		len = ft_strlen(shell->editor.buffer);
		ft_memmove(shell->editor.buffer + shell->editor.cursor, \
		shell->editor.buffer + shell->editor.cursor + 1, \
		ft_strlen(shell->editor.buffer + shell->editor.cursor + 1));
		shell->editor.buffer[len - 1] = 0;
	}
	return (1);
}

int			handle_backspace(t_editor *editor)
{
	size_t	len;

	if (!editor->cursor)
		return (1);
	len = ft_strlen(editor->buffer);
	editor->cursor--;
	ft_memmove(editor->buffer + editor->cursor, \
	editor->buffer + editor->cursor + 1, \
	ft_strlen(editor->buffer + editor->cursor + 1));
	editor->buffer[len - 1] = 0;
	return (1);
}
