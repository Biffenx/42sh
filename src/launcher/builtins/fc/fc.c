/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:56:23 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/31 20:14:37 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**https://www.unix.com/man-page/posix/1P/FC/
**
** Bits 1-4 in options are reserved for the flags and the fifth bit
** indicates possible error during builtin execution.
**
** Flags:
** 0 = -e editor
**		Use the editor named by editor to edit the commands.
**		The editor string is a utility name, subject to search
**		via the PATH variable (see the Base Definitions volume
**		of POSIX.1-2008, Chapter 8, Environment Variables).
**		The value in the FCEDIT variable  shall	be used as a default
**		when -e is not specified. If FCEDIT is null or unset,
**		ed shall be used as the editor.
** 1 = l (The  letter  ell.)
**		List the commands rather than invoking an editor on them.
**		The commands shall be written in the sequence indicated by
**		the first and last operands, as affected by -r, with each
**		command preceded by the command number.
** 2 = n
**		Suppress command numbers when listing with -l.
** 3 = r
**		Reverse the order of the commands listed (with -l)
**		or edited (with neither -l nor -s).
** 4 = s
**		Re-execute the command without invoking an editor.
*/

static void	set_option(char c, int *options)
{
	c == 'e' ? *options |= 1 << 0 : 0;
	c == 'l' ? *options |= 1 << 1 : 0;
	c == 'n' ? *options |= 1 << 2 : 0;
	c == 'r' ? *options |= 1 << 3 : 0;
	c == 's' ? *options |= 1 << 4 : 0;	
}

static char	**parse_options(char **argv, int *options)
{
	size_t	i;
	char	c;

	*options = 0;
	while (*argv && **argv == '-' && ft_isalpha(*(*argv + 1)))
	{
		i = 1;
		while ((*argv)[i])
		{
			if (ft_strchr(FCOPT, (*argv)[i]))
				c = (*argv)[i];
			else
				c = 0;
			set_option(c, options);
			if (!c)
			{
				ft_dprintf(STDERR_FILENO, FC_ERR_OPT, (*argv)[i]);
				ft_dprintf(STDERR_FILENO, FC_SYNTAX);
				*options |= 1 << 5;
				return (argv);
			}
			i += 1;
		}
		argv += 1;
	}
	return (argv);
}

static void parse_editor(char ***argv, char **editor, int *options)
{
	if (**argv)
	{
		*editor = **argv;
		*argv += 1;
		return ;
	}
	ft_putstr(FC_ERR_EDIT);
	*options |= 1 << 5;
}

static void verify_arguments(char **argv, int *options)
{
	if (*argv && *(argv + 1) && *(argv + 2))
	{
		ft_printf(STR_ARG_ERR, "fc");
		*options |= 1 << 5;
	}
}

int	fc(char **argv)
{
	int		options;
	char	*editor;

	options = 0;
	editor = FCEDIT;
	argv = parse_options(argv, &options);
	if (options & 1 << 0)
		parse_editor(&argv, &editor, &options);
	if (g_debug)
		fc_debug(options, editor);
	verify_arguments(argv, &options);
	if (options & 1 << 5)
		return (1);
	else if (options & 1 << 1)
		list_entries(argv, &options);
	else
		create_file(argv, &options);
	return (options & 1 << 5);
}
