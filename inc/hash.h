/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:11:34 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/14 15:07:41 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# define HASH_SIZE 300

typedef struct s_hash
{
	char	*key;
	char	*value;
}	t_hash;

int		hash_put(t_hash *map, char *key, char *value);
char	*hash_get(t_hash *map, char *key);
void	hash_delete(t_hash *map, char *key);
void	hash_purge(t_hash *map);
void	hash_display(t_hash *map);

#endif
