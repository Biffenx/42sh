/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:23:33 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 11:25:07 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	move_cursor_right(t_editor *editor)
{
	if (editor->buffer[editor->x])
		editor->x++;
	return (1);
}

int	move_cursor_left(t_editor *editor)
{
	if (editor->x > 0)
		editor->x--;
	return (1);
}
