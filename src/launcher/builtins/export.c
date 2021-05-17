/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:37:49 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/17 09:59:30 by jochumwilen      ###   ########.fr       */
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

int export_builtin(char **argv)
{
	int	i;
	int	print;

	i = 1;
	print = 0;
	if (ft_strequ(argv[i], "-p"))
	{
		print = 1;
		i += 1;
	}
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			export_argument(argv[i], print);
		else
			export_variable(argv[i], print);
		i += 1;
	}
	g_shell->env = environ;
	return (0);
}
