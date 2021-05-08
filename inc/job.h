/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:53:53 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/08 17:41:49 by vkuokka          ###   ########.fr       */
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
	struct s_process	*next;
	char				**argv;
	char				*path;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
}						t_process;

/* 
** A job is a pipeline of processes.
*/

typedef struct			s_job
{
	struct s_job		*next;
	int					launched;
	int					foreground;
	char				*command;
	t_process 			*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdin;
	int					stdout;
	int					stderr;
}						t_job;

/*
** Job creation.
*/

t_job					*create_job(t_token **tokens);
void					job_debug(t_job *job);
char					**tokens_to_array(t_token **tokens);
char					*find_path(char *command);

/*
** Job control.
*/

t_job					*find_job(pid_t pgid);
int						job_is_stopped(t_job *job);
int						job_is_completed(t_job *job);
void					put_job_in_foreground(t_job *job, int cont);
void					put_job_in_background(t_job *job, int cont);
int						mark_process_status(pid_t pid, int status);
void					update_status(void);
void					wait_for_job(t_job *job);
void					format_job_info(t_job *job, const char *status);
void					do_job_notification(void);
void					mark_job_as_running(t_job *job);
void 					continue_job(t_job *job, int foreground);
void					free_job(t_job *job);

#endif
