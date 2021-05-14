/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:06:24 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/14 12:31:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Hash functions for shell internal variable and alias implemetation.
*/

static int	hash_index(char *key)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	while (key[i])
	{
		code += key[i];
		i += 1;
	}
	code %= ft_strlen(key);
	return (code);
}

int		hash_put(t_hash *map, char *key, char *value)
{
	int	i;

	i = hash_index(key);
	if (g_debug)
		ft_printf("key: %s\nvalue: %s\nindex:%i\n", key, value, i);
	while (i < HASH_SIZE && map[i].key)
	{
		i += 1;
	}
	if (i == HASH_SIZE)
		ft_dprintf(STDERR_FILENO, "42sh: Hash full, please remove or purge entries\n");
	else
	{
		map[i].key = ft_strdup(key);
		map[i].value = ft_strdup(value);
	}
	return (i);
}

char	*hash_get(t_hash *map, char *key)
{
	int	i;

	i = hash_index(key);
	if (g_debug)
		ft_printf("key: %s\nindex:%i\n", key, i);
	while (i < HASH_SIZE && !ft_strequ(map[i].key, key))
	{
		i += 1;
	}
	if (i == HASH_SIZE)
	{
		return (NULL);
	}
	return (map[i].value);
}

void	hash_delete(t_hash *map, char *key)
{
	int	i;

	i = hash_index(key);
	while (i < HASH_SIZE && !ft_strequ(map[i].key, key))
	{
		i += 1;
	}
	if (i == HASH_SIZE)
	{
		return ;
	}
	ft_strdel(&map[i].key);
	ft_strdel(&map[i].value);
}

void	hash_purge(t_hash *map)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		ft_strdel(&map[i].key);
		ft_strdel(&map[i].value);
		i += 1;
	}
}
