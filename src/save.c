/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:37:10 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 20:14:49 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 		save(t_shell *shell)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = open(HISTORY_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		return ;
	i = 0;
	while (i < HISTORY_SIZE)
	{
		ft_putendl_fd(shell->history[i], fd);
		i++;
	}
	close(fd);
}
