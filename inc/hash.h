/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:59:07 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/12 20:02:09 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# define HASH_SIZE			20

enum	              	  	e_arrays
{
	SH_ALIAS,
	SH_VARS,
    SH_ENV,
	SH_JOBS
}							t_arrays;

typedef struct				s_dict
{
	int			       		 key;
	char					**data;
}							t_dict;

#endif
