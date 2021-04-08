/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:25:18 by vkuokka           #+#    #+#             */
/*   Updated: 2021/04/08 20:08:42 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	find_index(char *str, int *options)
{
	int		i;

	if (ft_isdigit(str[0]) || (str[0] == '-' && ft_isdigit(str[1])))
		return (ft_atoi(str));
	i = 0;
	while (g_shell->history[i])
	{
		if (ft_strstr(g_shell->history[i], str))
			return (i);
		i += 1;
	}
	ft_putstr(FC_ERR_EVENT);
	*options |= 1 << 5;
	return (0);
}

static void	list_latest(char options)
{
	int		i;
	int		count;

	i = ft_arrlen(g_shell->history, HISTORY_SIZE) - 1;
	count = 0;
	if (!(options & 1 << 3))
	{
		i -= 15;
		i < 0 ? i = 0 : 0;
		while (i < HISTORY_SIZE && g_shell->history[i] && count < 16)
		{
			options & 1 << 2 ? ft_putendl(g_shell->history[i])
			: ft_printf("%-10d%s\n", i, g_shell->history[i]);
			i += 1;
			count += 1;
		}
		return ;
	}
	while (count < 16 && i >= 0)
	{
		options & 1 << 2 ? ft_putendl(g_shell->history[i])
		: ft_printf("%-10d%s\n", i, g_shell->history[i]);
		i -= 1;
		count += 1;
	}
}

static void	list_from(char *argv, int options)
{
	int		i;
	int		histsize;

	i = find_index(argv, &options);
	if (options &= 1 << 5)
		return ;
	histsize = ft_arrlen(g_shell->history, HISTORY_SIZE);
	i < 0 ? i = histsize + i : 0;
	i > histsize ? i = histsize - 1 : 0;
	i < 0 ? i = 0 : 0;
	if (!(options & 1 << 3))
	{
		while (i < histsize)
		{
			options & 1 << 2 ? ft_putendl(g_shell->history[i])
			: ft_printf("%-10d%s\n", i, g_shell->history[i]);
			i += 1;
		}
		return ;
	}
	histsize -= 1;
	while (histsize >= i)
	{
		options & 1 << 2 ? ft_putendl(g_shell->history[histsize])
		: ft_printf("%-10d%s\n", histsize, g_shell->history[histsize]);
		histsize -= 1;
	}
}

static void	list_to(char *from, char *to, int options)
{
	int 	i;
	int		j;
	int		histsize;

	i = find_index(from, &options);
	j = find_index(to, &options);
	if (options &= 1 << 5)
		return ;
	histsize = ft_arrlen(g_shell->history, HISTORY_SIZE);
	i < 0 ? i = histsize + i : 0;
	i > histsize ? i = histsize - 1 : 0;
	i < 0 ? i = 0 : 0;
	j < 0 ? j = histsize + j : 0;
	j > histsize ? j = histsize - 1 : 0;
	j < 0 ? j = 0 : 0;
	if (i <= j)
		while (i <= j)
		{
			options & 1 << 2 ? ft_putendl(g_shell->history[i])
			: ft_printf("%-10d%s\n", i, g_shell->history[i]);
			i += 1;
		}
	else if (i >= j)
		while (i >= j)
		{
			options & 1 << 2 ? ft_putendl(g_shell->history[i])
			: ft_printf("%-10d%s\n", i, g_shell->history[i]);
			i -= 1;
		}
}

void		list(char **argv, char options)
{
	if (!*argv)
		list_latest(options);
	else
	{
		if (!*(argv + 1))
			list_from(*argv, options);
		else
		{
			if (options & 1 << 3)
				ft_swap_str(argv, (argv + 1));
			list_to(*argv, *(argv + 1), options);
		}
	}
}