/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:05:35 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/08 18:06:23 by vkuokka          ###   ########.fr       */
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
		free(line);
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
		write(2, ERR_HISTFILE, ft_strlen(ERR_HISTFILE));
	else
	{
		entries(fd, shell);
		close(fd);
	}
}