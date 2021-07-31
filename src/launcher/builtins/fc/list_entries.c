/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 20:36:29 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/31 20:00:03 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void up(int *options, int one, int two)
{
	char **array;

	array = g_shell->history;
	while (one >= two)
	{
		if (*options & 1 << 2)
			ft_putendl(array[one]);
		else
			ft_printf("%-5d%s\n", one, array[one]);
		one -= 1;
	}
}

static void down(int *options, int one, int two)
{
	char **array;

	array = g_shell->history;
	while (one <= two)
	{
		if (*options & 1 << 2)
			ft_putendl(array[one]);
		else
			ft_printf("%-5d%s\n", one, array[one]);
		one += 1;
	}
}

static void	handle_arguments(int *options, int one, int two)
{
	if (one > two)
	{
		if (*options & 1 << 3)
			down(options, two, one);
		else 
			up(options, one, two);
	}
	else
	{
		if (*options & 1 << 3)
			up(options, two, one);
		else 
			down(options, one, two);
	}
	
}

void list_entries(char **argv, int *options)
{
	int len;

	len = ft_arrlen(g_shell->history, HISTORY_SIZE);
	if (!*argv)
	{
		if (*options & 1 << 3)
			up(options, parse_index(-1, len), parse_index(-15, len));
		else 
			down(options, parse_index(-15, len), parse_index(-1, len));
	}
	else if (*argv && !*(argv + 1))
	{
		if (*options & 1 << 3)
			up(options, parse_index(HISTORY_SIZE, len), parse_index(ft_atoi(*argv), len));
		else 
			down(options, parse_index(ft_atoi(*argv), len), parse_index(HISTORY_SIZE, len));
	}
	else
		handle_arguments(options, parse_index(ft_atoi(*argv), len), parse_index(ft_atoi(*(argv + 1)), len));
}
