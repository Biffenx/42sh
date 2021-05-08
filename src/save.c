/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:37:10 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/08 18:05:56 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	entries(int fd, t_shell *shell)
{
	int		i;

	i = 0;
	while (i < HISTORY_SIZE)
	{
		ft_putendl_fd(shell->history[i], fd);
		i += 1;
	}
}

void 		save(t_shell *shell)
{
	int		fd;

	fd = open(HISTORY_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		write(2, ERR_HISTFILE, ft_strlen(ERR_HISTFILE));
	else
	{
		entries(fd, shell);
		close(fd);
	}
}
