/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:02:53 by srouhe            #+#    #+#             */
/*   Updated: 2021/05/11 12:44:29 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "type.h"

/*
** https://man7.org/linux/man-pages/man1/type.1p.html
**
** The standard output of type contains information about each
** operand in an unspecified format. The information provided
** typically identifies the operand as a shell built-in, function,
** alias, or keyword, and where applicable, may display the
** operand's pathname.
*/

static void builtin(char *command)
{
	if (isbuiltin(command))
		ft_printf("%s is a shell builtin\n", command);

}

static void binary(char *command)
{
	char	*path;

	if ((path = find_path(command)))
	{
		ft_printf("%s is a binary file (%s)\n", command, path);
		free(path);
	}
}

static void alias(char *command)
{
	t_hashmap *object;
	size_t	i;
	char	*key;
	char	*value;

	object = hash_search(SH_ALIAS, g_shell);
	i = 0;
	while (object->data[i])
	{
		key = split_key(object->data[i]);
		if (ft_strequ(key, command))
		{
			value = split_val(object->data[i]);
			ft_printf("%s is aliased to `%s`", command, value);
			free(value);
		}
		free(key);
		i += 1;
	}
}

int	type_builtin(char **argv)
{
	size_t    i;

	i = 1;
	while (argv[i])
	{
		builtin(argv[i]);
		binary(argv[i]);
		alias(argv[i]);
		i += 1;
	}
	return (0);
}