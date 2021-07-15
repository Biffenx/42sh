/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:58:41 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/07/15 14:53:58 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

# define FILENAME_MAX_SIZE 255

typedef struct s_autocomp
{
	char				command[FILENAME_MAX_SIZE * 2 + 1];
	struct s_autocomp	*next;
}						t_autocomp;

int	filename_character_allowed(char c);

#endif
