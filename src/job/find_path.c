/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:17:17 by vkuokka           #+#    #+#             */
/*   Updated: 2021/04/24 11:17:46 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*find_path(char *command)
{
	char	*path;
	size_t	i;
	char	**paths;

	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path = (char *)malloc(sizeof(char) * PATH_MAX);
	i = 0;
	while (g_shell->env[i] && !ft_strnequ(g_shell->env[i], "PATH=", 5))
		i += 1;
	paths = ft_strsplit(g_shell->env[i] + 5, ':');
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
