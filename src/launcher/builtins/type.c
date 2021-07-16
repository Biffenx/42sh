/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:02:53 by srouhe            #+#    #+#             */
/*   Updated: 2021/07/15 18:22:58 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** https://man7.org/linux/man-pages/man1/type.1p.html
**
** The standard output of type contains information about each
** operand in an unspecified format. The information provided
** typically identifies the operand as a shell built-in, function,
** alias, or keyword, and where applicable, may display the
** operand's pathname.
**
** Keywords are the words whose meaning has already been explained
** to the shell. The keywords cannot be used as variable names because
** of it is a reserved words with containing reserved meaning.
**
** Ie. if, else, while, do, done are keywords if these are implemented
** into shell.
*/

static int	builtin(char *command)
{
	if (isbuiltin(command))
	{
		ft_printf("%s is a shell builtin\n", command);
		return (0);
	}
	return (1);
}

static int	binary(char *command)
{
	char	*path;

	if ((path = find_path(command)))
	{
		ft_printf("%s is a binary file (%s)\n", command, path);
		free(path);
		return (0);
	}
	return (1);
}

static int	alias(char *command)
{
	char	*value;

	value = hash_get(g_shell->alias, command);
	if (value)
	{
		ft_printf("%s is aliased to `%s`\n", command, value);
		return (0);
	}
	return (1);
}

static int	keyword(char *command)
{
	if (!command)
		return (0);
	return (1);
}

int	type_builtin(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (builtin(argv[i]) && binary(argv[i])
			&& alias(argv[i]) && keyword(argv[i]))
			ft_dprintf(STDERR_FILENO, "42sh: type: %s: not found\n", argv[i]);
		i += 1;
	}
	return (0);
}
