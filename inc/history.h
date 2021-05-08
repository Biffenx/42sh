/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:45:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/08 18:13:36 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/*
** Fc builtin definitions
*/

# define FCEDIT "nano"
# define FCFILE "/var/tmp/42shfcfile.txt"
# define FCOPT "elrns"

/*
** Core history management.
*/

void		add_entry(char *cmd, t_shell *shell);
int			browse_up(t_shell *shell);
int			browse_down(t_shell *shell);
void		search_history(t_shell *shell);
int			exclamation(t_shell *shell);
size_t		parse(t_shell *shell, size_t i, char *tmp);
void		fetch(t_shell *shell);
void 		save(t_shell *shell);

/*
** Fc builtin prototypes.
*/

void 		list(char **argv, char options);
void		create_file(char **argv, int options);
int			find_index(char *str, int *options);
int			parse_index(int nbr, int histsize);
void		execute_fc(char *editor, int options);
void		fc_debug(int options);


#endif
