/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:37:49 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/27 12:56:34 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://man7.org/linux/man-pages/man1/export.1p.html
*/

static void	export_variable(char *key, int print)
{
	char	*value;

	value = hash_get(g_shell->vars, key);
	ft_printf("value: %s\n", value);
	if (!value)
		return ;
	if (!setenv(key, value, 1) && print)
		ft_printf("export %s=%s\n", key, value);
}

static void	export_argument(char *data, int print)
{
	char	*key;
	char	*value;

	key = data;
	data = ft_strchr(data, '=');
	*data = '\0';
	value = data + 1;
	if (!*key || !*value)
		return ;
	if (!setenv(key, value, 1) && print)
		ft_printf("export %s=%s\n", key, value);
}

static void	export_all(int print)
{
	size_t	i;
	t_hash 	*map;

	i = 0;
	map = g_shell->vars;
	while (i < HASH_SIZE)
	{
		if (map[i].key && !setenv(map[i].key, map[i].value, 1) && print)
			ft_printf("export %s=%s\n", map[i].key, map[i].value);
		i += 1;
	}
}

int	export_builtin(char **argv)
{
	int	print;

	print = 0;
	if (ft_strequ(*argv, "-p"))
	{
		print = 1;
		argv +=1 ;
	}
	if (!*argv)
		export_all(print);
	while (*argv)
	{
		if (ft_strchr(*argv, '='))
			export_argument(*argv, print);
		else
			export_variable(*argv, print);
		argv += 1;
	}
	return (0);
}
