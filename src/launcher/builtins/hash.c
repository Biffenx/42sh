/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 09:37:58 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 12:37:20 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/hash.1p.html
*/

static void	set_option(char c, int *options)
{
	c == 'r' ? *options |= 1 << 0 : 0;
	c == 0 ? *options |= 1 << 5 : 0;
}

static char	**parse_options(char **argv, int *options)
{
	size_t	i;
	char	c;

	*options = 0;
	while (*argv && **argv == '-')
	{
		i = 1;
		while ((*argv)[i])
		{
			if (ft_strchr(HASHOPT, (*argv)[i]))
				c = (*argv)[i];
			else
				c = 0;
			set_option(c, options);
			if (!c)
			{
				ft_dprintf(STDERR_FILENO, HASH_ERR_OPT, (*argv)[i]);
				ft_dprintf(STDERR_FILENO, HASH_SYNTAX);
				return (argv);
			}
			i += 1;
		}
		argv += 1;
	}
	return (argv);
}

int		hash_builtin(char **argv)
{
	int i;
	t_hash *map;
	int options;

	i = 0;
	map = g_shell->paths;
	parse_options(argv, &options);
	if (options & 1 << 5)
		return (1);
	else if (options & 1 << 0)
		hash_purge(map);
	else
		while (i < HASH_SIZE)
		{
			if (map[i].key && map[i].value)
			ft_putendl(map[i].value);
			i += 1;
		}
	return (0);
}
