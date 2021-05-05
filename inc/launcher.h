/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:14:31 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/05 14:16:51 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_H
# define LAUNCHER_H

# define BUILTIN_ARR	"exit", "jobs", "fc", "echo"
# define BUILTIN_SLOTS	4
# define BUILTIN_LEN	5

int			isbuiltin(char *command);
void		launch_job(t_job *job, int foreground);
void		launch_process(t_process *process, pid_t pgid, int infile, int outfile, int errfile, int foreground);
int			run_builtin(char **argv);

/*
** BUILTINS
*/

void		shell_exit();
int			jobs(char **argv);
int 		fc(char **argv);
int			echo(char **argv);

#endif
