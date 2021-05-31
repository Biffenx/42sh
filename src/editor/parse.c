/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 20:15:40 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/29 22:54:07 by vkuokka          ###   ########.fr       */
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
	i = HISTORY_SIZE - 1;
	while (!shell->history[i])
		i--;
	i -= num - 1;
	if (i < 0)
		i = 0;
	add(shell->history[i], shell);
	return (ft_count_digits_only(num, 10) + 1);
}

static size_t	tail(t_shell *shell, size_t start, char *tmp)
{
	int			i;
	int			num;

	i = start + 2;
	num = 0;
	while (ft_isdigit(tmp[i]))
	{
		i > 0 ? num *= 10 : 0;
		num += (tmp[i] - '0');
		i++;
	}
	i = num - 1;
	if (i >= HISTORY_SIZE)
		{
			i = HISTORY_SIZE - 1;
			while (!shell->history[i] && i >= 0)
				i--;
		}
	add(shell->history[i], shell);
	return (ft_count_digits_only(num, 10) + 2);
}

static size_t	word(t_shell *shell, size_t start, char *tmp)
{
	int			i;
	char		*str;
	size_t		length;

	i = start + 1;
	while (ft_isalpha(tmp[i]))
		i++;
	str = ft_strsub(tmp, start + 1, i - start);
	i = 0;
	while (i < HISTORY_SIZE && shell->history[i] \
	&& !ft_strstr(shell->history[i], str))
		i++;
	add(shell->history[i], shell);
	length = ft_strlen(str);
	free(str);
	return (length + 1);
}

size_t		parse(t_shell *shell, size_t i, char *tmp)
{
	if (tmp[i + 1] == '!')
	{
		add(shell->history[ft_arrlen(shell->history, HISTORY_SIZE) - 1], shell);
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
