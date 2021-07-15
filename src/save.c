/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:37:10 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 19:19:45 by jwilen           ###   ########.fr       */
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
		free(shell->history[i]);
		i += 1;
	}
}

void 	save(t_shell *shell)
{
	int		fd;

	fd = open(shell->history_file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		write(2, HIST_ERR_FILE, ft_strlen(HIST_ERR_FILE));
	else
	{
		entries(fd, shell);
		close(fd);
	}
}
