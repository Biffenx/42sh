/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:06:06 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/06 13:11:18 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			process_debug(t_process *first)
{
	t_process	*process;
	size_t		i;

	process = first;
	while (process)
	{
		i = 0;
		while (process->argv[i])
		{
			ft_printf("[%d] %s\n", i, process->argv[i]);
			i += 1;
		}
		process = process->next;
	}
}

void		job_debug(t_job *job)
{
	size_t	i;

	i = 0;
	ft_putstr("\n--JOB DEBUG--\n");
	while (job)
	{
		ft_printf("%i\ncommand: %s\n", i, job->command);
		process_debug(job->first_process);
		ft_printf("foreground: %d\n\n", job->foreground);
		job = job->next;
		i++;
	}
}