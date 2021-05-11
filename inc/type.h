/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 11:16:27 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/11 11:17:13 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Type builtin command definitions
*/

# define TYPE_EXEC_ERR 1

# define TYPE_USAGE     "type: usage: type [-afptP] name [name ...]"
# define TYPE_OPTS      "afptP"

# define TYPE_A 		(1 << 0)
# define TYPE_F		    (1 << 1)
# define TYPE_P			(1 << 2)
# define TYPE_T			(1 << 3)
# define TYPE_CAPP		(1 << 4)
# define TYPE_NUL       (1 >> 1)