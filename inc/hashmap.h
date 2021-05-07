/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:59:07 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/07 11:18:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# define HASH_SIZE			200

enum	              	  	e_arrays
{
	SH_ENV,
	SH_VARS,
	SH_ALIAS,
}							t_arrays;

typedef struct				s_hashmap
{
	int			       		 key;
	char					**data;
}							t_hashmap;

#endif
