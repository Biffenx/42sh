/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 10:39:43 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:31:44 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	cut_left(t_shell *shell)
{
	char	tmp[ARG_MAX];

	ft_bzero(tmp, ARG_MAX);
	ft_bzero(shell->editor.clipboard, ARG_MAX);
	ft_memmove(shell->editor.clipboard,
		shell->editor.buffer, shell->editor.cursor);
	ft_memmove(tmp, shell->editor.buffer + shell->editor.cursor,
		ft_strlen(shell->editor.buffer + shell->editor.cursor));
	ft_bzero(shell->editor.buffer, ARG_MAX);
	ft_memmove(shell->editor.buffer, tmp, ft_strlen(tmp));
	shell->editor.cursor = 0;
	return (1);
}

static int	cut_right(t_shell *shell)
{
	ft_bzero(shell->editor.clipboard, ARG_MAX);
	ft_memmove(shell->editor.clipboard,
		shell->editor.buffer + shell->editor.cursor,
		ft_strlen(shell->editor.buffer + shell->editor.cursor));
	ft_bzero(shell->editor.buffer + shell->editor.cursor,
		ARG_MAX - shell->editor.cursor);
	return (1);
}

static int	paste_clipboard(t_shell *shell)
{
	size_t	buffersize;
	size_t	clipboardsize;

	buffersize = ft_strlen(shell->editor.buffer);
	clipboardsize = ft_strlen(shell->editor.clipboard);
	if (buffersize + clipboardsize >= ARG_MAX)
		return (1);
	if (shell->editor.buffer[shell->editor.cursor])
		ft_memmove(shell->editor.buffer + shell->editor.cursor
			+ ft_strlen(shell->editor.clipboard),
			shell->editor.buffer + shell->editor.cursor,
			ft_strlen(shell->editor.buffer + shell->editor.cursor));
	ft_memmove(shell->editor.buffer + shell->editor.cursor,
		shell->editor.clipboard, ft_strlen(shell->editor.clipboard));
	return (1);
}

int	check_clipboard_keys(int key, t_shell *shell)
{
	if (key == CTRL_U)
		return (cut_left(shell));
	else if (key == CTRL_K)
		return (cut_right(shell));
	else if (key == CTRL_P)
		return (paste_clipboard(shell));
	else
		return (0);
}
