/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 21:25:09 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/01 21:42:21 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include "shell.h"

static void	edit(char **args)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		exit(1);
	path = find_path(args[0]);
	if (pid == 0)
		execve(path, args, environ);
	else
		wait(&pid);
	free(path);
}

static void	execute(int *options)
{
	int		fd;
	char	*buff;

	fd = open(FCFILE, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(FC_ERR_FD, STDERR_FILENO);
		*options |= 1 << 5;
	}
	while (get_next_line(fd, &buff))
	{
		reset(PROMPT_NORMAL, g_shell);
		g_shell->mode |= LOADJOB;
		ft_strlcat(g_shell->editor.buffer, buff, ARG_MAX);
		preprocess(g_shell->editor.buffer, g_shell);
		free(buff);
	}
	close(fd);
}

void	execute_file(char *editor, int *options)
{
	char	*args[3];

	args[0] = editor;
	args[1] = FCFILE;
	args[2] = NULL;
	edit(args);
	execute(options);
}