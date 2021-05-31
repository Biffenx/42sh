/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:30:03 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/29 15:12:37 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	reset(char *prompt, t_shell *shell)
{
	shell->mode = shell->mode & INTERACTIVE;
	ft_bzero(shell->editor.prompt, PROMPT_SIZE);
	ft_strcat(shell->editor.prompt, prompt);
	ft_bzero(shell->editor.buffer, ARG_MAX);
	shell->editor.cursor = 0;
	shell->alias_index = 0;
	shell->history_index = ft_arrlen(shell->history, HISTORY_SIZE);
}
