/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuiltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:13:41 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 18:33:23 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	isbuiltin(char *command)
{
	size_t		i;
	static char	builtin[BUILTIN_SLOTS][BUILTIN_LEN] = {BUILTIN_ARR};

	i = 0;
	while (i < BUILTIN_SLOTS)
	{
		if (ft_strequ(builtin[i], command))
			return (1);
		i += 1;
	}
	return (0);
}
