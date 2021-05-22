/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:37:49 by vkuokka           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/16 22:09:08 by jochumwilen      ###   ########.fr       */
=======
/*   Updated: 2021/05/17 13:21:12 by vkuokka          ###   ########.fr       */
>>>>>>> d73f5dc90cce85ebe28b30c0c981dfd7f907912d
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
<<<<<<< HEAD

=======
>>>>>>> d73f5dc90cce85ebe28b30c0c981dfd7f907912d
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
	return (0);
}
