/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exclamation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:26:30 by vkuokka           #+#    #+#             */
/*   Updated: 2021/07/30 21:45:33 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	head(char *tmp, char **tmp2, t_shell *shell)
{
	int			i;
	int			num;

	i = 1;
	num = 0;
	while (ft_isdigit(tmp[i]))
	{
		i > 0 ? num *= 10 : 0;
		num += (tmp[i] - '0');
		i++;
	}
	i = parse_index(num, ft_arrlen(shell->history, HISTORY_SIZE));
	*tmp2 = ft_strjoin(tmp, shell->history[i]);
	return (ft_count_digits_only(num, 10) + 1);
}

static int	tail(char *tmp, char **tmp2, t_shell *shell)
{
	int			i;
	int			num;

	i = 2;
	num = 0;
	while (ft_isdigit(tmp[i]))
	{
		i > 0 ? num *= 10 : 0;
		num += (tmp[i] - '0');
		i++;
	}
	i = parse_index(num *= -1, ft_arrlen(shell->history, HISTORY_SIZE));
	*tmp2 = ft_strjoin(tmp, shell->history[i]);
	return (ft_count_digits_only(num, 10) + 2);
}

static int	word(char *tmp, char **tmp2, t_shell *shell)
{
	int			i;
	char		*str;
	size_t		length;

	i = 1;
	while (ft_isalpha(tmp[i]))
		i++;
	str = ft_strsub(tmp, 1, i);
	i = 0;
	while (i < HISTORY_SIZE && shell->history[i] \
	&& !ft_strstr(shell->history[i], str))
		i++;
	*tmp2 = ft_strjoin(tmp, shell->history[i]);
	length = ft_strlen(str);
	free(str);
	return (length + 1);
}

static int	parse(char *tmp, char **tmp2, t_shell *shell)
{
	if (*(tmp + 1) == '!')
	{
		*tmp2 = ft_strjoin(tmp + 2, shell->history[ft_arrlen(shell->history, HISTORY_SIZE) - 1]);
		return (2);
	}
	else if (ft_isdigit(*(tmp + 1)))
		return (head(tmp, tmp2, shell));
	else if (*(tmp + 1) == '-')
		return (tail(tmp, tmp2, shell));
	else if (ft_isprint(*(tmp + 1)))
		return (word(tmp, tmp2, shell));
	return (1);
}

void			parse_exclamation(char **data, t_shell *shell)
{
	int			i;
	char		*tmp;
	char		*tmp2;
	char		*new;

	i = 0;
	tmp = *data;
	while ((tmp = ft_strchr(tmp, '!')))
	{
		if (!*(tmp + 1))
			break ;
		*tmp = '\0';
		i = parse(tmp, &tmp2, shell);
		if (tmp2)
		{
			new = ft_strjoin(tmp2, tmp + i);
			ft_strdel(&tmp2);
		}
		else
			new = ft_strjoin(tmp, tmp + i);
		ft_strdel(data);
		*data = new;
		tmp = new;
	}
}
