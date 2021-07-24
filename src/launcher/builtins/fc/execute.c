/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 09:57:05 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/24 10:56:29 by vkuokka          ###   ########.fr       */
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
		execve(path, args, environ);
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
		reset(PROMPT_NORMAL, g_shell);
		g_shell->mode |= LOADJOB;
		if (ft_strlen(buff) < ARG_MAX)
			ft_strcat(g_shell->editor.buffer, buff);
		preprocess(g_shell->editor.buffer, g_shell);
		free(buff);
	}
	close(fd);
}

void	execute_fc(char *editor, int options)
{
	char	*args[3];

	args[0] = editor;
	args[1] = FCFILE;
	args[2] = NULL;
	if (!(options & 1 << 4))
		launch_editor(args, options);
	execute_file(options);
}
