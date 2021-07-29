/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 09:37:58 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/29 13:18:09 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/hash.1p.html
*/

static int	parse_options(char ***argv)
{
	int		options;
	size_t	i;

	options = 0;
	while (**argv && ***argv == '-' && ft_isalpha(*(**argv + 1)))
	{
		i = 1;
		while ((**argv)[i] != '\0')
		{
			if (!ft_strchr(HASHOPT, (**argv)[i]))
			{
				ft_dprintf(STDERR_FILENO, HASH_ERR_OPT, (**argv)[i]);
				ft_dprintf(STDERR_FILENO, HASH_SYNTAX);
				options |= 1 << 5;
				return (options);
			}
			(**argv)[i] == 'r' ? options |= 1 << 0 : 0;
			i += 1;
		}
		*argv += 1;
	}
	return (options);
}

int		hash_builtin(char **argv)
{
	int i;
	t_hash *map;
	int options;

	i = 0;
	map = g_shell->paths;
	options = parse_options(&argv);
	if (options & 1 << 5)
		return (1);
	else if (options & 1 << 0)
	{
		hash_purge(map);
		return (0);
	}
	if (!*argv)
		while (i < HASH_SIZE)
		{
			if (map[i].key && map[i].value)
			ft_putendl(map[i].value);
			i += 1;
		}
	return (0);
}
