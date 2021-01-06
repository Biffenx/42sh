/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:30:03 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/06 10:47:22 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	reset(char *prompt, t_shell *shell)
{
	shell->mode = shell->mode & INTERACTIVE;
	if (!prompt)
	{
		/* create_prompt(editor->prompt);
		load_filenames(editor->ac, editor->prompt->cwd); */
	}
	else
	{
		/* ft_bzero(editor->prompt->prompt, PROMPT_SIZE);
		ft_strcat(editor->prompt->prompt, prompt); */
	}
	ft_bzero(shell->editor.buffer, ARG_MAX);
	shell->editor.length = 0;
	shell->editor.x = 0;
	shell->editor.y = 0;
}
