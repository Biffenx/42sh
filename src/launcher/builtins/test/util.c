/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:40:31 by jwilen            #+#    #+#             */
/*   Updated: 2021/05/16 22:04:22 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ft_free_ntab(char **tabs)
{
	int		i;

	if (!tabs)
		return ;
	i = -1;
	while (tabs[++i])
		ft_memdel((void *)&(tabs[i]));
	ft_memdel((void *)&tabs);
}

int	free_new_argv(char **new_argv, int ret)
{
	ft_free_ntab(new_argv);
	return (ret);
}

static int	check_size(char **args)
{
	int		i;
	int		ac;

	i = 1;
	ac = 0;
	while (args[ac])
		ac++;
	while (args[i] && !ft_strcmp(args[i], "!"))
		i++;
	i--;
	return (ac - i);
}

static void	init_ints(int *i, int *k, int *inv)
{
	*i = 1;
	*k = 1;
	*inv = 0;
}

char	**check_inv(char **args, int *inv)
{
	int		i;
	int		k;
	int		size;
	char	**new_args;

	init_ints(&i, &k, inv);
	size = check_size(args);
	new_args = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	new_args[0] = ft_strdup(args[0]);
	while (args[i])
	{
		if (!ft_strcmp(args[i], "!"))
			*inv += 1;
		else
			break ;
		i++;
	}
	while (args[i])
		new_args[k++] = ft_strdup(args[i++]);
	new_args[size] = NULL;
	return (new_args);
}
