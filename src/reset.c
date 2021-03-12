/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:30:03 by vkuokka           #+#    #+#             */
/*   Updated: 2021/03/12 13:09:38 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	reset(char *prompt, t_shell *shell)
{
	shell->mode = shell->mode & INTERACTIVE;
	if (!prompt)
	{
		// create_prompt(&shell->editor.prompt); ?
		// load_filenames(editor->ac, editor->prompt->cwd); ?
	}
	else
	{
		ft_bzero(shell->editor.prompt, PROMPT_SIZE);
		ft_strcat(shell->editor.prompt, prompt);
	}
	ft_bzero(shell->editor.buffer, ARG_MAX);
	shell->editor.cursor = 0;
	shell->history_index = ft_arrlen(shell->history, HISTORY_SIZE);
	// clean_paths(editor->ac); ?
}
