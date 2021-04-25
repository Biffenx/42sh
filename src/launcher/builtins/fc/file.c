/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:28:53 by vkuokka           #+#    #+#             */
/*   Updated: 2021/04/25 10:41:55 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	write_entry(char *argv, int fd, int options)
{
	int		i;
	int		histsize;

	i = find_index(argv, &options);
	if (options &= 1 << 5)
		return ;
	histsize = ft_arrlen(g_shell->history, HISTORY_SIZE);
	i = parse_index(i, histsize);
	ft_putendl_fd(g_shell->history[i], fd);
}

static void	write_between(char *from, char *to, int fd, int options)
{
	int 	i;
	int		j;
	int		histsize;

	i = find_index(from, &options);
	j = find_index(to, &options);
	if (options &= 1 << 5)
		return ;
	histsize = ft_arrlen(g_shell->history, HISTORY_SIZE);
	i = parse_index(i, histsize);
	j = parse_index(j, histsize);
	if (i <= j)
		while (i <= j)
		{
			ft_putendl_fd(g_shell->history[j], fd);
			j -= 1;
		}
	else if (i >= j)
		while (i >= j)
		{
			ft_putendl_fd(g_shell->history[j], fd);
			j += 1;
		}
}

void		create_file(char **argv, int options)
{
	int		fd;

	fd = open(FCFILE, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd(FC_ERR_FD, STDERR_FILENO);
		options |= 1 << 5;
		return ;
	}
	if (!*argv)
		write_entry("-1", fd, options);
	else if (!*(argv + 1))
		write_entry(*argv, fd, options);
	else
	{
		if (options & 1 << 3)
			ft_swap_str(argv, (argv + 1));
		write_between(*argv, *(argv + 1), fd, options);
	}
	close(fd);
}
