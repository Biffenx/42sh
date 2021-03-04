/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:38:38 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/04 19:03:41 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		free_process(t_process *process)
{
	t_process	*tmp;

	while (process)
	{
		ft_arrfree(process->argv);
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

void			free_job(t_job *job)
{
	free(job->command);
	free_process(job->first_process);
}
