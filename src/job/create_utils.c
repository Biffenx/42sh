/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 08:12:46 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/29 08:02:39 by jochumwilen      ###   ########.fr       */
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
		ft_printf("token: %s %d \n", token->data, length);
		write(1, "X", 1);
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
