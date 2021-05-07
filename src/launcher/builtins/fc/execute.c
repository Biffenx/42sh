/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 09:57:05 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/07 11:50:18 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	launch_editor(char **args, int options)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
	{
		options |= 1 << 5;
		return ;
	}
	path = find_path(args[0]);
	if (pid == 0)
		execve(path, args, hash_search(SH_ENV, g_shell)->data);
	else
		wait(&pid);
	free(path);
}

static void	execute_file(int options)
{
	int		fd;
	char	*buff;

	fd = open(FCFILE, O_RDONLY);
	if (fd < 0)
	{
		options |= 1 << 5;
		return ;
	}
	while (get_next_line(fd, &buff))
	{
		preprocess(buff, g_shell);
		ft_strdel(&buff);
	}
	close(fd);
}

void		execute_fc(char *editor, int options)
{
	char	*args[3];

	args[0] = editor;
	args[1] = FCFILE;
	args[2] = NULL;
	if (!(options & 1 << 4))
		launch_editor(args, options);
	execute_file(options);
}