/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 10:52:54 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 18:27:12 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://www.man7.org/linux/man-pages/man1/hash.1p.html
*/

static void	print_table(t_hash *table)
{
	size_t	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (table[i].key && table[i].value)
			ft_printf("%s=%s\n", table[i].key, table[i].value);
		i += 1;
	}
}

static int	parse_and_put(t_hash *table, char *data)
{
	char	*value;
	char	*key;

	key = data;
	data = ft_strchr(data, '=');
	if (!data)
		return (1);
	*data = '\0';
	value = data + 1;
	if (*key && hash_put(table, key, value) > -1)
		return (0);
	return (1);
}

static int	command_set_1(char **argv)
{
	if (ft_strequ(argv[1], "help"))
		ft_putstr(HASH_HELP);
	else if (ft_strequ(argv[1], "purge"))
		hash_purge(g_shell->table);
	else if (ft_strequ(argv[1], "display"))
		print_table(g_shell->table);
	else
	{
		ft_dprintf(STDERR_FILENO, HASH_SYNTAX);
		return (1);
	}
	return (0);
}

static int	command_set_2(char **argv)
{
	if (ft_strequ(argv[1], "put"))
		return (parse_and_put(g_shell->table, argv[2]));
	else if (ft_strequ(argv[1], "get"))
	{
		ft_printf("%s\n", hash_get(g_shell->table, argv[2]));
		return (0);
	}
	else if (ft_strequ(argv[1], "delete"))
		return (hash_delete(g_shell->table, argv[2]));
	ft_dprintf(STDERR_FILENO, HASH_SYNTAX);
	return (1);
}

int	hash_builtin(char **argv)
{
	if (argv[1] && !argv[2])
		return (command_set_1(argv));
	else if (argv[1] && argv[2] && !argv[3])
		return (command_set_2(argv));
	ft_dprintf(STDERR_FILENO, HASH_SYNTAX);
	return (1);
}
