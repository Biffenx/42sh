/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 09:37:58 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/28 10:37:49 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/hash.1p.html
*/

int		hash_builtin(char **argv)
{
	int i;
	t_hash *map;

	ft_printf("%-10s %s\n", "hits", "command");
	i = 0;
	map = g_shell->utils;
	if (!*argv)
		while (i < HASH_SIZE)
		{
			if (map[i].key && map[i].value)
			ft_printf("%-10s %s\n", map[i].value, map[i].key);
			i += 1;
		}
	return (0);
}
