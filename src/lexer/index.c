/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:54:43 by srouhe            #+#    #+#             */
/*   Updated: 2021/07/20 13:26:46 by srouhe           ###   ########.fr       */
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

static int	tokenize_escape(t_lexer *lexer, char *input)
{
	if (lexer->data[1] == '\n')
	{
		ft_putendl("how to check when the line ends");
		add_token(lexer, ft_strsub(input, 0, 1), EXPAND_NL);
		return (1);
	}
	else if (lexer->data[1] && lexer->data[1] != '\\')
	{
		add_token(lexer, ft_strsub(input, 1, 1), STRING);
		return (2);
	}
	else
		return (1);
}

void		tokenize(t_lexer *lexer, char *input)
{
	int	i;

	i = 0;
	ft_strlcat(lexer->data, input, ARG_MAX);
	while (lexer->data[i] && ~ g_shell->mode & INTERRUPT)
	{
		if (lexer->data[i] == '\\')
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
