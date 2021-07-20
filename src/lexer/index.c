/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2021/07/20 17:51:00 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Add tokens to linked list:
**		Escaped characters
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

static int	tokenize_escape(t_lexer *lexer, char *input)
{
	int i;

	if (input[1] && input[1] == '\\')
	{
		add_token(lexer, ft_strsub(input, 1, 1), STRING);
		return (2);
	}
	i = 0;
	while (input[i] && input[i + 1] && input[i + 1] != ' ' && input[i + 1] != '\\' && !ft_strchr(OPERATORS, input[i]))
	{
		if (input[i] != '\\' && input[i + 1] && ft_strchr(OPERATORS, input[i + 1]))
			break;
		i++;
	}
	add_token(lexer, ft_strsub(input, 0, i + 1), ESCAPE);
	return (i + 1);
}

void		tokenize(t_lexer *lexer, char *input)
{
	int	i;

	i = 0;
	ft_strlcat(lexer->data, input, ARG_MAX);
	while (lexer->data[i] && ~ g_shell->mode & INTERRUPT)
	{
		if (lexer->data[i] == 92)
			i += tokenize_escape(lexer, &lexer->data[i]);
		else if (ft_strchr(OPERATORS, lexer->data[i]))
			i += tokenize_operator(lexer, &lexer->data[i]);
		else if (!ft_strncmp(OPT_LEXER, &lexer->data[i],
				ft_strlen(OPT_LEXER) - 1))
		{
			lexer->flags |= DEBUG_LEXER;
			i += ft_strlen(OPT_LEXER);
		}
		else if (!ft_strncmp(OPT_JOBS, &lexer->data[i],
				ft_strlen(OPT_JOBS) - 1))
		{
			lexer->flags |= DEBUG_JOBS;
			i += ft_strlen(OPT_JOBS);
		}
		else if (is_valid_char(lexer->data[i]))
			i += tokenize_string(lexer, &lexer->data[i]);
		else
			i++;
	}
	check_trailing(lexer);
	lexer->first = lexer->head;
}
