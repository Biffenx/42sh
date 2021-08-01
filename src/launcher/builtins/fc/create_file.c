/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 20:03:18 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/31 20:28:45 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void up(int one, int two, int fd)
{
	char **array;

	array = g_shell->history;
	while (one >= two)
	{
		ft_putendl_fd(array[one], fd);
		one -= 1;
	}
}

static void down(int one, int two, int fd)
{
	char **array;

	array = g_shell->history;
	while (one <= two)
	{
		ft_putendl_fd(array[one], fd);
		one += 1;
	}
}

static void	handle_arguments(int *options, int one, int two, int fd)
{
	if (one > two)
	{
		if (*options & 1 << 3)
			down(two, one, fd);
		else 
			up(one, two, fd);
	}
	else
	{
		if (*options & 1 << 3)
			up(two, one, fd);
		else 
			down(one, two, fd);
	}
	
}

static int	open_file(int *options)
{
	int fd;

	fd = open(FCFILE, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd(FC_ERR_FD, STDERR_FILENO);
		*options |= 1 << 5;
	}
	return (fd);
}

void create_file(char **argv, int *options)
{
	int len;
	int fd;

	len = ft_arrlen(g_shell->history, HISTORY_SIZE);
	fd = open_file(options);
	if (*options & 1 << 5)
		return ;
	if (!*argv)
		ft_putendl_fd(g_shell->history[parse_index(HISTORY_SIZE, len)], fd);
	else if (*argv && !*(argv + 1))
	{
		if (*options & 1 << 3)
			up(parse_index(HISTORY_SIZE, len), parse_index(ft_atoi(*argv), len), fd);
		else 
			down(parse_index(ft_atoi(*argv), len), parse_index(HISTORY_SIZE, len), fd);
	}
	else
		handle_arguments(options, parse_index(ft_atoi(*argv), len), parse_index(ft_atoi(*(argv + 1)), len), fd);
	close(fd);
}
