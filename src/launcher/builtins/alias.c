/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:16:30 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/15 09:38:26 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/alias.1p.html
*/

static void	find_alias(char *key)
{
	char	*value;

	value = hash_get(g_shell->alias, key);
	if (value)
		ft_printf("alias %s=%s\n", key, value);
	else
		ft_dprintf(STDERR_FILENO, "42sh: alias: %s: not found\n", key);
}

static void	add_alias(char *data)
{
	char	*value;
	char	*key;

	key = data;
	data = ft_strchr(data, '=');
	*data = '\0';
	value = data + 1;
	if (*key)
		hash_put(g_shell->alias, key, value);
	else
	{
		*ft_strchr(data, '\0') = '=';
		find_alias(data);
	}
}

static void	print_map(t_hash *map)
{
	size_t	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (map[i].key && map[i].value)
			ft_printf("alias %s='%s'\n", map[i].key, map[i].value);
		i += 1;
	}
}

int	alias_builtin(char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		print_map(g_shell->alias);
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			add_alias(argv[i]);
		else
			find_alias(argv[i]);
		i += 1;
	}
	return (0);
}
