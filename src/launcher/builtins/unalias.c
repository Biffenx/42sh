/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:39:03 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/02 19:57:39 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/unalias.1p.html
*/

int	unalias_builtin(char **argv)
{
	if (ft_strequ(*argv, "-a"))
	{
		hash_purge(g_shell->alias);
		return (0);
	}
	while (*argv)
	{
		hash_delete(g_shell->alias, *argv);
		argv += 1;
	}
	return (0);
}
