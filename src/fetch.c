/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:05:35 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 18:58:12 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		fetch(t_shell *shell)
{
	size_t	i;
	int		fd;
	char	*line;

	i = 0;
	while (i < HISTORY_SIZE)
	{
		shell->history[i] = NULL;
		i++;
	}
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) < ARG_MAX)
		{
			shell->history[i] = line;
			i++;
		}
	}
	close(fd);
}