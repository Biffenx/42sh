/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:39:03 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/12 10:03:50 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/unalias.1p.html
*/

static void	purge_list(char	**array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_strdel(&array[i]);
		i += 1;
	}
}

int	unalias_builtin(char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		return (0);
	if (ft_strequ(argv[i], "-a"))
		purge_list(hash_search(SH_ALIAS, g_shell)->data);
	else
	while (argv[i])
	{
		array_delete(SH_ALIAS, array_find(SH_ALIAS, argv[i]));
		i += 1;
	}
	return (0);
}
