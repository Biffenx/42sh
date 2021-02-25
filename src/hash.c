/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:47:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/02/25 13:30:53 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	hash_code(int key)
{
	return (key % HASH_SIZE);
}

void		hash_insert(int key, char **data, t_shell *shell)
{
	int		hash_index;
	t_dict	*item;

	item = (t_dict *)malloc(sizeof(t_dict));
	item->data = data;
	item->key = key;
	hash_index = hash_code(key);
	while (shell->dict[hash_index] != NULL && shell->dict[hash_index]->key != -1)
	{
		++hash_index;
		hash_index %= HASH_SIZE;
	}
	shell->dict[hash_index] = item;
}

t_dict		*hash_search(int key, t_shell *shell)
{
	int		hash_index;

	hash_index = hash_code(key);
	while (shell->dict[hash_index] != NULL)
	{
		if (shell->dict[hash_index]->key == key)
			return (shell->dict[hash_index]);
		++hash_index;
		hash_index %= HASH_SIZE;
	}
	return (NULL);
}
