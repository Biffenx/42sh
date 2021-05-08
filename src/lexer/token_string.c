/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:07:32 by srouhe            #+#    #+#             */
/*   Updated: 2021/05/08 17:13:17 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Parse quotes and check open squotes and dquotes
*/

static void	append_data(t_lexer *lexer, t_shell *shell)
{
	reset(PROMPT_QUOTE, shell);
	editor(shell);
	ft_strlcat(lexer->data, "\n", ARG_MAX);
	ft_strlcat(lexer->data, shell->editor.buffer, ARG_MAX);
}

static int	check_quoting(t_lexer *lexer, char *input, int i)
{
	int		j;
	int		quot;

	j = i;
	quot = next_quote(&input[i + 1], input[i]);
	while (quot == -1)
	{
		append_data(lexer, g_shell);
		if (g_shell->mode & INTERRUPT)
			return (-1);
		quot = next_quote(&input[i + 1], input[i]);
	}
	i += quot;
	input[i + 1] == '\'' ? \
		add_token(lexer, ft_strsub(&input[j + 1], 0, i), NOEXPAND) :\
		add_token(lexer, ft_strsub(&input[j + 1], 0, i), STRING);
	return (i + 2);
}

static int	token_exceptions(t_lexer *lexer, char *input, int i)
{
	if (lexer->last && lexer->last->type & MASK_REDIR && !ft_strncmp(input, "-", 1))
		add_token(lexer, ft_strsub(input, 0, i), DASH);
	else if (lexer->last && lexer->last->type & T_DLARR)
		add_token(lexer, ft_strsub(input, 0, i), HEREDOC);
	else if (lexer->last && lexer->last->type & MASK_REDIR && !(lexer->last->type & T_DLARR))
		add_token(lexer, ft_strsub(input, 0, i), FILENAME);
	else
		add_token(lexer, ft_strsub(input, 0, i), STRING);
	return (i);	
}
/*
** Make a string, filename, dash or heredoc token
*/

int			tokenize_string(t_lexer *lexer, char *input)
{
	int		i;
	int		quot;

	i = 0;
	while (is_valid_char(input[i]))
	{
		if (input[i] == '=' && (input[i + 1] == D_QUOTE || input[i + 1] == S_QUOTE))
		{
			quot = next_quote(&input[i + 2], input[i + 1]);
			i += quot + 2;
			add_token(lexer, ft_strsub(input, 0, i + 1), STRING);
			return (i + 2);
		}
		else if (input[i] == D_QUOTE || input[i] == S_QUOTE)
			return (check_quoting(lexer, input, i));
		i++;
	}
	return (token_exceptions(lexer, input, i));
}
