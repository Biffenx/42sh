/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:05:35 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/08 18:54:31 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	entries(int fd, t_shell *shell)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) < ARG_MAX)
		{
			shell->history[i] = line;
			i += 1;
		}
	}
}

void		fetch(t_shell *shell)
{
	int		i;
	int		fd;

	i = 0;
	while (i < HISTORY_SIZE)
	{
		shell->history[i] = NULL;
		i += 1;
	}
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		write(2, HIST_ERR_FILE, ft_strlen(HIST_ERR_FILE));
	else
	{
		entries(fd, shell);
		close(fd);
	}
}