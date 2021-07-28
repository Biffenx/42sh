/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:17:17 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/28 10:35:37 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Returns path to a executable binary file if found, else NULL is returned.
*/

static void save_utils(char *path)
{
	char *hits;
	char *tmp;

	hits = hash_get(g_shell->utils, path);
	if (hits)
	{
		tmp = ft_itoa(ft_atoi(hits) + 1);
		hash_put(g_shell->utils, path, tmp);
		free(tmp);
		return ;
	}
	hits = "1";
	hash_put(g_shell->utils, path, hits);
}

char	*find_path(char *command)
{
	char	**paths;
	char	*path;
	size_t	i;

	path = ft_strnew(PATH_MAX);
	if (!path)
		exit(1);
	i = 0;
	paths = ft_strsplit(hash_get(g_shell->vars, "PATH"), ':');
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
	save_utils(path);
	return (path);
}
