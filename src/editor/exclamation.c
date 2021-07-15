/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:12:54 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/15 16:28:46 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	init(size_t *i, char *tmp, t_shell *shell)
{
	i[0] = 0;
	i[1] = 0;
	ft_bzero(tmp, ARG_MAX);
	ft_strcat(tmp, shell->editor.buffer);
	reset(PROMPT_NORMAL, shell);
}

int	exclamation(t_shell *shell)
{
	size_t		i[2];
	char		tmp[ARG_MAX];
	int			parsed;

	init(i, tmp, shell);
	parsed = 0;
	while (tmp[i[0]])
	{
		if (tmp[i[0]] == '!' && ft_isprint(tmp[i[0] + 1]))
		{
			i[0] += parse(shell, i[0], tmp);
			i[1] = ft_strlen(shell->editor.buffer);
			parsed++;
		}
		else
		{
			shell->editor.buffer[i[1]] = tmp[i[0]];
			i[0]++;
			i[1]++;
		}
	}
	shell->editor.cursor = ft_strlen(shell->editor.buffer);
	return (parsed);
}
