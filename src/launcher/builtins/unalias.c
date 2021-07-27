/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:39:03 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/27 12:22:14 by vkuokka          ###   ########.fr       */
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
