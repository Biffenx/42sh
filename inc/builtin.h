/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 11:53:18 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 13:12:51 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILITIN_H
# define BUILTIN_H

/*
** Hash builtin definitons.
*/

# define HASHOPT "r"

/*
** Fc builtin definitions
*/

# define FCEDIT "nano"
# define FCFILE "/var/tmp/42shfcfile.txt"
# define FCOPT "elrns"

/*
** Fc builtin prototypes.
*/

void		fc_debug(int options, char *editor);

#endif
