/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 09:57:05 by vkuokka           #+#    #+#             */
/*   Updated: 2021/04/25 10:43:10 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	launch_editor(char **args, int options)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		options |= 1 << 5;
		return ;
	}
	if (pid == 0)
		execve(find_path(args[0]), args, g_shell->env);
	else
		wait(&pid);
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
		preprocess(buff, g_shell);
	close(fd);
	return ;
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