/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:48:06 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/12 15:21:12 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# define HASH_SIZE 200

enum	e_arrays
{
	SH_ENV,
	SH_VARS,
	SH_ALIAS,
} t_arrays;

typedef struct s_hashmap
{
	int		key;
	char	**data;
}	t_hashmap;

#endif
