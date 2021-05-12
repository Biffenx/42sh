/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:16:30 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/12 09:36:40 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/alias.1p.html
*/

int	alias_builtin(char **argv)
{
	int	i;
	char	*key;
	char	*val;

	i = 1;
	if (!argv[i])
		return (array_display(SH_ALIAS));
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			key = split_key(argv[i]);
			val = split_val(argv[i]);
			array_set(SH_ALIAS, key, val);
		}
		else
			array_display(SH_ALIAS);   
		i += 1;
	}
	return (0);
}
