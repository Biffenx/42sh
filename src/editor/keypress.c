/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:05:08 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:27:59 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	keypress(void)
{
	char	buffer[KEY_SIZE + 1];
	ssize_t	bytes;
	size_t	i;
	int		key;

	bytes = read(STDIN_FILENO, buffer, KEY_SIZE);
	buffer[bytes] = '\0';
	i = -1;
	key = 0;
	while (buffer[++i])
		key += buffer[i];
	return (key);
}
