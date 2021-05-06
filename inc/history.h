/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:45:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/06 14:12:54 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define FCEDIT "nano"
# define FCFILE "/var/tmp/42shfcfile.txt"
# define FCOPT "elrns"
# define FC_ERR_PATH "%s: command not found\n"
# define FC_ERR_OPT "fc: bad option: -%c\n"
# define FC_ERR_EDIT "fc: -e: option requires an argument\n"
# define FC_ERR_FD "fc: could not open fcfile\n"
# define FC_ERR_ARG "fc: too many arguments\n"
# define FC_ERR_EXEBCK "fc: history events can't be executed backwards, aborted\n"
# define FC_ERR_EVENT "fc: event not found: %s\n"
# define FC_ERR_REPARG "fc: replace argument invalid\n"

void		add_entry(t_shell *shell);
int			browse_up(t_shell *shell);
int			browse_down(t_shell *shell);
void		search_history(t_shell *shell);
int			exclamation(t_shell *shell);
void		fetch(t_shell *shell);
void 		save(t_shell *shell);

void 		list(char **argv, char options);
void		create_file(char **argv, int options);
int			find_index(char *str, int *options);
int			parse_index(int nbr, int histsize);
void		execute_fc(char *editor, int options);
void		fc_debug(int options);


#endif
