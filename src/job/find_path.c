/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:17:17 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/11 12:25:47 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Returns path to a executable binary file if found, else NULL is returned.
*/

static char	**search_paths(void)
{
	char	**env;
	int		i;

	env = hash_search(SH_VARS, g_shell)->data;
	i = 0;
	while (env[i] && !ft_strnequ(env[i], "PATH=", 5))
	{
		i += 1;
	}
	return (ft_strsplit(env[i] + 5, ':'));
}

char		*find_path(char *command)
{
	char	**paths;
	char	*path;
	size_t	i;

	path = ft_strnew(PATH_MAX);
	if (!path)
		exit(1);
	i = 0;
	paths = search_paths();
	ft_strcat(path, command);
	while (access(path, X_OK) == -1 && paths[i])
	{
		ft_bzero(path, PATH_MAX);
		ft_strcat(path, paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, command);
		i += 1;
	}
	ft_arrfree(paths);
	if (access(path, X_OK) == -1)
		ft_strdel(&path);
	return (path);
}
