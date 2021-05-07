/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:17:17 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/07 11:48:16 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*find_path(char *command)
{
	char	**env;
	char	*path;
	size_t	i;
	char	**paths;

	env = hash_search(SH_VARS, g_shell)->data;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path = (char *)malloc(sizeof(char) * PATH_MAX);
	i = 0;
	while (env[i] && !ft_strnequ(env[i], "PATH=", 5))
		i += 1;
	paths = ft_strsplit(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		ft_bzero(path, PATH_MAX);
		ft_strcat(path, paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, command);

		if (access(path, X_OK) == 0)
			break ;
		i += 1;
	}
	ft_arrfree(paths);
	return (path);
}
