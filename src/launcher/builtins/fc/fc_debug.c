/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:10:38 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 13:13:16 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	fc_debug(int options, char *editor)
{
	ft_print_bits(options, 8);
	ft_putendl("");
	ft_putendl(editor);
}
