/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:06:24 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/23 11:25:21 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Calculate hash index value.
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
	return (code * 2);
}

/*
** Add key and value pair into hashmap. On success returns the index of added pair
** and on failure returns -1.
*/

int		hash_put(t_hash *map, char *key, char *value)
{
	int	i;

	if (!key || !*key)
		return (-1);
	i = hash_index(key);
	hash_delete(map, key);
	if (g_debug)
	 ft_printf("key: %s\nvalue: %s\nindex: %i\n\n", key, value, i);
	while (i < HASH_SIZE && map[i].key)
	{
		i += 1;
	}
	if (i == HASH_SIZE)
	{
		return (-1);
	}
	else
	{
		map[i].key = ft_strdup(key);
		map[i].value = ft_strdup(value);
	}
	return (i);
}

/*
** Find a value of the key. On success returns the value and on failure returns NULL.
*/

char	*hash_get(t_hash *map, char *key)
{
	int	i;

	if (!key || !*key)
		return (NULL);
	i = hash_index(key);
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

/*
** Delete key and value pair from hashmap. On success returns 0
** and on failure returns 1.
*/

int		hash_delete(t_hash *map, char *key)
{
	int	i;

	if (!key || !*key)
		return (1);
	i = hash_index(key);
	while (i < HASH_SIZE && !ft_strequ(map[i].key, key))
	{
		i += 1;
	}
	if (i == HASH_SIZE)
	{
		return (1);
	}
	ft_strdel(&map[i].key);
	ft_strdel(&map[i].value);
	return (0);
}

/*
** Delete all of the key and value pairs from hashmap.
*/

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
