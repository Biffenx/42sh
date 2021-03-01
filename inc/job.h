/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:53:53 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/01 19:47:52 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H

# include <unistd.h>
# include <term.h>
# include "lexer.h"

/*
** A process is a single process.
*/

typedef struct			s_process
{
	struct s_process	*next;			/* next process in pipeline */
	char				**argv;			/* for exec */
	pid_t				pid;			/* process ID */
	char				completed;		/* true if process has completed */
	char				stopped;		/* true if process has stopped */
	int					status;			/* reported status value */
}						t_process;

/* 
** A job is a pipeline of processes.
*/

typedef struct			s_job
{
	struct s_job		*next;			/* next active job */
	int					foreground;
	char				*command;		/* command line, used for messages */
	t_process 			*first_process;	/* list of processes in this job */
	pid_t				pgid;			/* process group ID */
	char				notified;		/* true if user told about stopped job */
	struct termios		tmodes;			/* saved terminal modes */
	int					stdin;			/* standard i/o channels */
	int					stdout;
	int					stderr;
}						t_job;

t_job					*create_job(t_token **tokens);
void 					job_debug();
char					**tokens_to_array(t_token **tokens);

#endif
