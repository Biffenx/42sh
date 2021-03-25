/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:25:18 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/25 17:09:33 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	latest(char options)
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

void		list(char **argv, char options)
{
	if (!*argv)
		latest(options);
}