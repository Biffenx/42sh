/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:53:53 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/02 09:27:31 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_H
# define JOB_H

# include <unistd.h>
# include <term.h>
# include "lexer.h"

typedef struct s_re_ag
{
	enum {
		REDIR = 0,
		AGGRE = 1
	}				e_flag;
	union
	{
		struct		s_re
		{
			int		*heredoc;
			char	*redir;
			char	*file;
		}			t_re;
		struct		s_ag
		{
			char	*n;
			char	*sign;
			char	*word;
		}			t_ag;
	} node;
	struct s_re_ag	*next;
}					t_re_ag;

/*
** A process is a single process.
*/

typedef struct s_process
{
	struct s_process	*next;
	char				**argv;
	char				condition;
	char				*path;
	t_re_ag				*re_ag;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
	int					exit;
}	t_process;

/* 
** A job is a pipeline of processes.
*/

typedef struct s_job
{
	int					id;
	struct s_job		*next;
	int					launched;
	int					foreground;
	char				*command;
	t_process			*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdin;
	int					stdout;
	int					stderr;
}	t_job;

/*
** Job creation.
*/
int						determine_id(t_job *first);
char					*join_tokens(t_token *tokens);
t_job					*create_job(t_token **tokens);
void					job_debug(t_job *job);
char					**tokens_to_array(t_token **tokens);
char					*find_path(char *command);
char					resolve_condition(t_token **token);

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
void					continue_job(t_job *job, int foreground);
void					free_job(t_job *job);

/*
** Redirection.
*/



t_re_ag					*create_re_ag_list(t_token **tokens);
void					parse_redir_aggre_list(t_re_ag *l, t_job *j, \
						int *outfile);
void					switch_redir_node(t_re_ag *l, t_job *j, int *outfile);
void					dup42(int in, int out, int err);
void					set_redir_tokens(t_re_ag *new_node, t_token *token);
void					set_aggre_tokens(t_re_ag *new_node, t_token *token);
void					set_re_ag_e_flag(t_re_ag *new_node, t_token *token);

#endif
