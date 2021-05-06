/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:56:23 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/06 14:14:40 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Bits 1-4 in options are reserved for the flags and the fifth bit
** indicates possible error during builtin execution.
*/

static void parse_editor(char **editor, char ***argv, int *options)
{
	if (!**argv)
	{
		ft_putstr_fd(FC_ERR_EDIT, STDERR_FILENO);
		*options |= 1 << 5;
	}
	else
	{
		*editor = **argv;
		*argv += 1;
	}
}

static int parse_options(char ***argv, char **editor)
{
	int		options;
	size_t	i;

	options = 0;
	*argv += 1;
	while (**argv && ***argv == '-' && ft_isalpha(*(**argv + 1)))
	{
		i = 1;
		while ((**argv)[i] != '\0')
		{
			if (!ft_strchr(FCOPT, (**argv)[i]))
			{
				ft_putstr_fd(FC_ERR_OPT, STDERR_FILENO);
				options |= 1 << 5;
				return (options);
			}
			(**argv)[i] == 'e' ? options |= 1 << 0 : 0;
			(**argv)[i] == 'l' ? options |= 1 << 1 : 0;
			(**argv)[i] == 'n' ? options |= 1 << 2 : 0;
			(**argv)[i] == 'r' ? options |= 1 << 3 : 0;
			(**argv)[i] == 's' ? options |= 1 << 4 : 0;
			i += 1;
		}
		*argv += 1;
	}
	if (options & 1 << 0)
		parse_editor(editor, argv, &options);
	return (options);
}

static void	verify_arguments(char **argv, int *options)
{
	if (argv[0] && argv[1] && argv[2])
	{
		ft_putstr_fd(FC_ERR_ARG, STDERR_FILENO);
		*options |= 1 << 5;
	}
}

int 		fc(char **argv)
{
	int		options;
	char	*editor;

	editor = FCEDIT;
	options = parse_options(&argv, &editor);
	verify_arguments(argv, &options);
	if (g_debug)
		fc_debug(options);
	if (options & 1 << 5)
		return (1);
	if (options & 1 << 1)
		list(argv, options);
	else
	{
		create_file(argv, options);
		execute_fc(editor, options);
	}
	return (0);
}
