/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:01:52 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/15 09:40:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://man7.org/linux/man-pages/man1/set.1p.html
*/

static void	add_variable(char *data)
{
	char	*key;
	char	*value;

	key = data;
	data = ft_strchr(data, '=');
	*data = '\0';
	value = data + 1;
	if (*key)
		hash_put(g_shell->vars, key, value);	
}

static void	print_map(t_hash *map)
{
	size_t	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (map[i].key && map[i].value)
			ft_printf("%s=%s\n", map[i].key, map[i].value);
		i += 1;
	}
}

int	set_builtin(char **argv)
{
	int	i;

	i = 1;
	if (!argv[i])
		print_map(g_shell->vars);
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			add_variable(argv[i]);
		i += 1;	
	}
	return (0);
}
