/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2021/05/29 11:15:01 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Add tokens to linked list:
**		Control tokens:
**			"&&", "||", "|", ";", ">>", "<<", "<&", "<>", "&>", ">|", ">", "<", "&"
**		Strings (parse quotes and dquotes)
**	Update count and flags to lexer
*/

static char	*append_data(t_shell *shell)
{
	reset(PROMPT_PIPE, shell);
	editor(shell);
	return (shell->editor.buffer);
}

static void	check_trailing(t_lexer *lexer)
{
	if (lexer->last->type & T_PIPE)
	{
		append_data(g_shell);
		tokenize(lexer, g_shell->editor.buffer);
	}
}

void	tokenize(t_lexer *lexer, char *input)
{
	int	i;
	t_lexer	*current;

	i = 0;
	ft_strlcat(lexer->data, input, ARG_MAX);
	while (lexer->data[i] && ~g_shell->mode & INTERRUPT)
	{
		if (ft_strchr(OPERATORS, lexer->data[i]))
			i += tokenize_operator(lexer, &lexer->data[i]);
		else if (!ft_strncmp(OPT_LEXER, &lexer->data[i], ft_strlen(OPT_LEXER) - 1))
		{
			lexer->flags |= DEBUG_LEXER;
			i += ft_strlen(OPT_LEXER);
		}
		else if (!ft_strncmp(OPT_JOBS, &lexer->data[i], ft_strlen(OPT_JOBS) - 1))
		{
			lexer->flags |= DEBUG_JOBS;
			i += ft_strlen(OPT_JOBS);
		}
		else if (is_valid_char(lexer->data[i]))
			i += tokenize_string(lexer, &lexer->data[i]);
		else
			i++;
	}
	current = lexer;

		ft_printf("J: %s\n", current->data);

	check_trailing(lexer);
	lexer->first = lexer->head;
}
