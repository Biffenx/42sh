/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:14:31 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 13:44:05 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_H
# define LAUNCHER_H

/*
** List of built-in shell commands.
*/

# define BUILTIN_ARR	"exit", "jobs", "fc", "cd", "echo", "type", "alias", "unalias", "set", "export", "unset", "fg", "hash", "bg", "map", "test", "history"
# define BUILTIN_SLOTS	17
# define BUILTIN_LEN	8

# define EXEC_OK 1
# define EXEC_ERROR 0

int			isbuiltin(char *command);
void		launch_job(t_job *job, int foreground);
void		launch_process(t_process *process, t_job *job, pid_t pgid, int infile, int outfile, int errfile, int foreground);
int			run_builtin(char **argv, t_process *process, t_job *job, int infile, int outfile, int errfile);
void		set_signals_default(void);
void		set_file_descriptors(t_process *process, t_job *job, int infile, int outfile, int errfile);
void		reset_file_descriptors(int in, int out, int err);

/*
** Builtin command protoypes.
*/

int 		fc(char **argv);
int			alias_builtin(char **args);
int			bg_builtin(char **argv);
int			cd_builtin(char **argv);
int			echo_builtin(char **argv);
void		exit_builtin();
int			export_builtin(char **argv);
int			fg_builtin(char **argv);
int			hash_builtin(char **argv);
int			history_builtin(char **argv);
int			map_builtin(char **argv);
int			jobs_builtin(char **argv);
int			set_builtin(char **argv);
int			test_builtin(char **argv);
int         type_builtin(char **args);
int			unalias_builtin(char **argv);
int			unset_builtin(char **argv);

/*
** Builtin command utils
*/

char	current(t_job *job);
char	*state(t_job *job);

#endif
