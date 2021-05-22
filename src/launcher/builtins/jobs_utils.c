/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:23:00 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/22 13:34:36 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	current(t_job *job)
{
	if (job == g_shell->current)
		return ('+');
	else if (job == g_shell->previous)
		return ('-');
	else
		return (' ');
}

char	*state(t_job *job)
{
	if (job_is_completed(job))
		return ("Done");
	else if (job_is_stopped(job))
		return ("Stopped");
	else
		return ("Running");
}
