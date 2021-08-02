/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:11:34 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/31 15:22:35 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# define HASH_SIZE 100

typedef struct s_hash
{
	char	*key;
	char	*value;
}	t_hash;

int		hash_put(t_hash *map, char *key, char *value);
char	*hash_get(t_hash *map, char *key);
int		hash_key_exists(t_hash *map, char *key);
int		hash_delete(t_hash *map, char *key);
void	hash_purge(t_hash *map);

#endif
