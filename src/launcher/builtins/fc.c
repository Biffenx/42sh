/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 11:56:23 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/14 12:49:50 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int parse_options(char ***argv)
{
	int		options;
	size_t	i;

	options = 0;
	*argv += 1;
	while (**argv && ***argv == '-')
	{
		i = 1;
		while ((**argv)[i] != '\0')
		{
			(**argv)[i] == 'e' ? options |= 1 << 0 : 0;
			(**argv)[i] == 'l' ? options |= 1 << 1 : 0;
			(**argv)[i] == 'n' ? options |= 1 << 2 : 0;
			(**argv)[i] == 'r' ? options |= 1 << 3 : 0;
			(**argv)[i] == 's' ? options |= 1 << 4 : 0;
			i += 1;
		}
		*argv += 1;
	}
	return (options);
}

int 		fc(char **argv)
{
	char	options;

	options = parse_options(&argv);
	ft_print_bits(options, 8);
	ft_putendl(*argv);
	return (0);
}
