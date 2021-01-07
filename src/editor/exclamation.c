/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:12:54 by vkuokka           #+#    #+#             */
/*   Updated: 2021/01/07 21:52:16 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		add(char *entry, t_shell *shell)
{
	if (!entry || ft_strlen(entry) >= ARG_MAX - ft_strlen(shell->editor.buffer))
		return ;
	else
		ft_strcat(shell->editor.buffer, entry);
}

static size_t	head(t_shell *shell, size_t start, char *tmp)
{
	int			i;
	int			num;

	i = start + 1;
	num = 0;
	while (ft_isdigit(tmp[i]))
	{
		i > 0 ? num *= 10 : 0;
		num += (tmp[i] - '0');
		i++;
	}
	num = HISTORY_SIZE - num;
	if (num < 0)
		num = 0;
	add(shell->history[num], shell);
	return (ft_count_digits_only(num, 10) + 1);
}

static size_t	tail(t_shell *shell, size_t start, char *tmp)
{
	size_t		i;
	size_t		num;

	i = start + 2;
	num = 0;
	while (ft_isdigit(tmp[i]))
	{
		i > 0 ? num *= 10 : 0;
		num += (tmp[i] - '0');
		i++;
	}
	num--;
	if (num >= HISTORY_SIZE)
		num = HISTORY_SIZE - 1;
	add(shell->history[num], shell);
	return (ft_count_digits_only(num, 10) + 2);
}

static size_t	word(t_shell *shell, size_t start, char *tmp)
{
	size_t		i;
	char		*str;
	size_t		length;

	i = start + 1;
	while (ft_isalpha(tmp[i]))
		i++;
	str = ft_strsub(tmp, start + 1, i - start);
	i = 0;
	while (i < HISTORY_SIZE && !ft_strstr(shell->history[i], str))
		i++;
	add(shell->history[i], shell);
	length = ft_strlen(str);
	free(str);
	return (length + 1);
}

static size_t	parse(t_shell *shell, size_t i, char *tmp)
{
	if (tmp[i + 1] == '!')
	{
		add(shell->history[0], shell);
		return (2);
	}
	else if (ft_isdigit(tmp[i + 1]))
		return (head(shell, i, tmp));
	else if (tmp[i + 1] == '-')
		return (tail(shell, i, tmp));
	else if (ft_isalpha(tmp[i + 1]))
		return (word(shell, i, tmp));
	return (1);
}

int				exclamation(t_shell *shell)
{
	size_t		i;
	size_t		j;
	char		tmp[ARG_MAX];
	int			parsed;

	i = 0;
	j = 0;
	ft_bzero(tmp, ARG_MAX);
	ft_strcat(tmp, shell->editor.buffer);
	reset(PROMPT_NORMAL, shell);
	parsed = 0;
	while (tmp[i])
		if (tmp[i] == '!' && ft_isprint(tmp[i + 1]))
		{
			i += parse(shell, i, tmp);
			j = ft_strlen(tmp);
			parsed++;
		}
		else
		{
			shell->editor.buffer[j] = tmp[i];
			i++;
			j++;
		}
	shell->editor.length = ft_strlen(shell->editor.buffer);
	shell->editor.x = shell->editor.length;
	return (parsed);
}
