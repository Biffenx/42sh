/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:45:45 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 13:03:58 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

/*
** Core history management.
*/

void		add_entry(t_token *tokens, t_shell *shell);
int			browse_up(t_shell *shell);
int			browse_down(t_shell *shell);
void		search_history(t_shell *shell);
void		fetch(t_shell *shell);
void		save(t_shell *shell);

int			parse_index(int nbr, int histsize);

#endif
