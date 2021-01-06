/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:16:33 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 20:14:43 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		add_entry(t_shell *shell)
{
	size_t	i;
	char	*entry;

	i = HISTORY_SIZE - 1;
	entry = ft_strdup(shell->editor.buffer);
	free(shell->history[i]);
	while (i > 0)
	{
		shell->history[i] = shell->history[i - 1];
		i--;
	}
	shell->history[0] = entry;
}
