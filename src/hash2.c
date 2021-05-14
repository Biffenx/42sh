/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:43:16 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/14 12:56:36 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	hash_display(t_hash *map)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (map[i].key)
			ft_printf("alias %s=%s\n", map[i].key, map[i].value);
		i += 1;
	}
}
