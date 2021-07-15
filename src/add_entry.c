/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:16:33 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 19:16:55 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_entry(char *cmd, t_shell *shell)
{
	int		i;
	char	*entry;

	i = ft_arrlen(shell->history, HISTORY_SIZE);
	if (i >= HISTORY_SIZE)
	{
		i = 0;
		free(shell->history[i]);
		while (i < HISTORY_SIZE)
		{
			shell->history[i] = shell->history[i + 1];
			i += 1;
		}
		i -= 1;
	}
	entry = ft_strdup(cmd);
	if (!entry)
		return ;
	shell->history[i] = entry;
}
