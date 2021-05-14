/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:39:03 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/14 12:55:46 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/unalias.1p.html
*/

int	unalias_builtin(char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		return (0);
	if (ft_strequ(argv[i], "-a"))
		hash_purge(g_shell->alias);
	else
	{
		while (argv[i])
		{
			hash_delete(g_shell->alias, argv[i]);
			i += 1;
		}
	}
	return (0);
}
