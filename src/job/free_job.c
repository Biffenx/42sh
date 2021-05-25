/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:38:38 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/25 20:50:56 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		free_process(t_process *process)
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

void			free_job(t_job *job)
{
	if (g_shell->current == job)
		g_shell->current = NULL;
	free(job->command);
	free_process(job->first_process);
	free(job);
	job = NULL;
}
