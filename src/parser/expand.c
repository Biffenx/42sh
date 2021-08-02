/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:23:11 by srouhe            #+#    #+#             */
/*   Updated: 2021/08/02 19:56:34 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*check_value(char *key, t_shell *shell)
{
	char	*value;

	value = hash_get(shell->vars, key);
	free(key);
	if (!value)
		return ("");
	else
		return (value);
}

static void	parse_exit(char **data, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;

	tmp = *data;
	tmp2 = ft_itoa(shell->exit);
	*data = ft_strreplace(*data, "$?", tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

static void	parse_dollar(char **data, t_shell *shell)
{
	int			i;
	char		*tmp;
	char		*tmp2;
	char		*new;

	parse_exit(data, shell);
	i = 1;
	tmp = *data;
	while ((tmp = ft_strchr(tmp, '$')))
	{
		*tmp = '\0';
		while (ft_isalpha(tmp[i]))
			i += 1;
		tmp2 = ft_strjoin(*data,
				check_value(ft_strsub(tmp + 1, 0, i - 1), shell));
		new = ft_strjoin(tmp2, tmp + i);
		ft_strdel(&tmp2);
		ft_strdel(data);
		*data = new;
		tmp = new;
	}
}

static void	parse_tilde(char **data, t_shell *shell)
{
	char		*tmp;
	char		*value;

	if (ft_strchr(*data, '~'))
	{
		value = hash_get(shell->vars, "HOME");
		if (!value)
			value = "";
		tmp = *data;
		*data = ft_strreplace(tmp, "~", value);
		ft_strdel(&tmp);
	}
}

/*
** Expand aliases, $ and ~ characters in tokens and heredocs
*/

void	expand_tokens(t_lexer *lexer, t_shell *shell)
{
	t_token	*token;
	t_token *del;

	token = lexer->head;
	while (token)
	{
		if (hash_key_exists(shell->alias, token->data))
		{
			if (token->prev && ft_strequ(token->prev->data, "unalias"))
				PASS;
			else
			{
				tokenize_alias(lexer, &token, shell);
				del = token;
				token = token->next;
				token_del(del);
				continue ;
			}
		}
		if (token->type & T_STR)
		{
			parse_dollar(&token->data, shell);
			parse_tilde(&token->data, shell);
			parse_exclamation(&token->data, shell);
		}
		if (token->heredoc)
		{
			parse_dollar(&token->heredoc, shell);
			parse_tilde(&token->heredoc, shell);
		}
		if (token->type & T_NOEXPAND)
			token->type |= (1 << STRING);
		if (token->type & T_ESCAPE)
			token->data = ft_strreplace(token->data, "\\", "");
		// ft_putendl(token->data);
		token = token->next;
	}
	// lexer_debug(*lexer);
}
