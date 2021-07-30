/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 20:36:29 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 22:04:58 by vkuokka          ###   ########.fr       */
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
}
