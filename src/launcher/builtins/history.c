/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 13:33:58 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 14:00:43 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	set_option(char c, int *options)
{
	c == 'c' ? *options |= 1 << 0 : 0;	
}

static char	**parse_options(char **argv, int *options)
{
	size_t	i;
	char	c;

	*options = 0;
	while (*argv && **argv == '-')
	{
		i = 1;
		while ((*argv)[i])
		{
			if (ft_strchr(HISTOPT, (*argv)[i]))
				c = (*argv)[i];
			else
				c = 0;
			set_option(c, options);
			if (!c)
			{
				ft_dprintf(STDERR_FILENO, HIST_ERR_OPT, (*argv)[i]);
				ft_dprintf(STDERR_FILENO, HIST_SYNTAX);
				return (argv);
			}
			i += 1;
		}
		argv += 1;
	}
	return (argv);
}

static void	clear_history(char **array)
{
	int i;

	i = 0;
	while (i < HISTORY_SIZE && array[i])
	{
		ft_strdel(&array[i]);
		i += 1;
	}
}

static void	loop_history(char **array)
{
	int i;

	i = 0;
	while (i < HISTORY_SIZE && array[i])
	{
		ft_printf("%-5d%s\n", i, array[i]);
		i += 1;
	}
}

int	history_builtin(char **argv)
{
	int options;

	argv = parse_options(argv, &options);
	if (*argv)
	{
		ft_printf(STR_ARG_ERR, "history");
		return (1);
	}
	if (options & 1 << 0)
		clear_history(g_shell->history);
	else
		loop_history(g_shell->history);
	return (0);
}
