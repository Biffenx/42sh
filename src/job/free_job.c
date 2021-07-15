/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:38:38 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:49:58 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	free_process(t_process *process)
{
	t_process	*tmp;

	while (process)
	{
		ft_arrfree(process->argv);
		free(process->path);
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

void	free_job(t_job *job)
{
	if (g_shell->current == job)
		g_shell->current = NULL;
	free(job->command);
	free_process(job->first_process);
	free(job);
	job = NULL;
}
