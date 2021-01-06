/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:28:57 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 12:16:59 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			handle_eof(t_shell *shell)
{
	size_t	len;

	if (!shell->editor.buffer[0])
		shell->mode = shell->mode | ENDOFFILE;
	else if (shell->editor.buffer[shell->editor.x])
	{
		len = ft_strlen(shell->editor.buffer);
		ft_memmove(shell->editor.buffer + shell->editor.x, \
		shell->editor.buffer + shell->editor.x + 1, \
		ft_strlen(shell->editor.buffer + shell->editor.x + 1));
		shell->editor.buffer[len - 1] = 0;
		shell->editor.length--;
	}
	return (1);
}

int			handle_backspace(t_editor *editor)
{
	size_t	len;

	if (!editor->x)
		return (1);
	len = ft_strlen(editor->buffer);
	editor->x--;
	ft_memmove(editor->buffer + editor->x, \
	editor->buffer + editor->x + 1, \
	ft_strlen(editor->buffer + editor->x + 1));
	editor->buffer[len - 1] = 0;
	editor->length--;
	return (1);
}
