/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:14:31 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/30 17:43:01 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_H

# define LAUNCHER_H

# define BUILTIN_ARR	"exit", "jobs", "fc"
# define BUILTIN_SLOTS	3
# define BUILTIN_LEN	5

/*
** Fc
*/

# define FCEDIT "nano"
# define FCFILE "/var/tmp/42shfcfile.txt"
# define FC_ERR_PATH "%s: command not found\n"
# define FC_ERR_OPT "fc: bad option: -%c\n"
# define FC_ERR_EDIT "fc: -e: option requires an argument\n"
# define FC_ERR_FD "fc: could not open fcfile\n"
# define FC_ERR_ARG "fc: too many arguments\n"
# define FC_ERR_EXEBCK "fc: history events can't be executed backwards, aborted\n"
# define FC_ERR_EVENT "fc: event not found: %s\n"
# define FC_ERR_REPARG "fc: replace argument invalid\n"

void 		list(char **argv, char options);

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

#endif
