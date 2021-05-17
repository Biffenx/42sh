/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 08:12:46 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/17 08:38:22 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	determine_id(t_job *first)
{
	t_job *job;

	job = first;
	if (job)
	{
		while (job->next)
		{
			job = job->next;
		}
		return (job->id + 1);
	}
	else
		return (1);
}

char	*join_tokens(t_token *tokens)
{
	t_token *token;
	size_t	length;
	char	*command;

	token = tokens;
	length = 0;
	while (token)
	{
		length += ft_strlen(token->data);
		if (token->next)
			length += 1;
		token = token->next;
	}
	command = ft_strnew(length);
	token = tokens;
	while (token)
	{
		ft_strcat(command, token->data);
		if (token->next)
			ft_strlcat(command, " ", length);
		token = token->next;
	}
	return (command);
}
