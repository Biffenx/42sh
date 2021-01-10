/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:23:11 by srouhe            #+#    #+#             */
/*   Updated: 2021/01/10 13:37:27 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*helper(char *var, t_shell *shell)
{
	if (!ft_strcmp(var, "$?"))
		return (ft_itoa(shell->status));
	else if (getenv(var + 1))
		return (ft_strdup(getenv(var + 1)));
	else
		return (NULL);
}

static void			clean(char *value, char *tmp)
{
	free(value);
	ft_strdel(&tmp);
}

static void		parse_dollar(char **data, t_shell *shell)
{
	int			i;
	char		*tmp;
	char		*var;
	char		*value;

	i = 1;
	tmp = *data;
	while ((tmp = ft_strchr(tmp, '$')))
	{
		while (tmp[i] != '\0' && tmp[i] != '$' && tmp[i] != '"'
				&& !ft_isspace(tmp[i]))
			i++;
		var = ft_strsub(tmp, 0, i);
		value = helper(var, shell);
		if (value)
		{
			tmp = *data;
			*data = ft_strreplace(tmp, var, value);
			clean(value, tmp);
			tmp = *data;
		}
		tmp++;
		i = 1;
		free(var);
	}
}

static void		parse_tilde(char **data)
{
	char		*tmp;
	char		*value;

	tmp = *data;
	while ((tmp = ft_strchr(tmp, '~')))
	{
		if ((value = getenv("HOME")))
		{
			tmp = *data;
			*data = ft_strreplace(tmp, "~", value);
			ft_strdel(&tmp);
			tmp = *data;
		}
		tmp++;
	}
}

/*
** Expand aliases, $ and ~ characters in tokens and heredocs
*/

void			expand_tokens(t_lexer *lexer, t_shell *shell)
{
	t_token 	*token;

	token = lexer->head;
	while (token)
	{
		if (token->type & T_STR)
		{
			parse_dollar(&token->data, shell);
			parse_tilde(&token->data);
			// tokenize_alias(lexer, &token); ?
		}
		if (token->heredoc)
		{
			parse_dollar(&token->heredoc, shell);
			parse_tilde(&token->heredoc);
		}
		if (token->type & T_NOEXPAND)
			token->type |= (1 << STRING);
		token = token->next;
	}
}
