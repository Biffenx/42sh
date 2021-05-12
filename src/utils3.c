/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:19:22 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/12 10:09:19 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Utility functions for accessing and modifying global shell arrays
*/

int				array_display(int hashkey)
{
    int		i;
	t_hashmap	*item;

    i = 0;
	item = hash_search(hashkey, g_shell);
    if (!item)
        return (EXEC_OK);
    while (item->data[i])
    {
        if (hashkey == SH_ALIAS)
            ft_printf("alias %s\n", item->data[i]);
        else
            ft_putendl(item->data[i]);
        i += 1;
    }
    return (EXEC_OK);
}

void		    array_delete(int hashkey, int pos)
{
	int		i;
    t_hashmap  *item;

    item = hash_search(hashkey, g_shell);
	ft_strdel(&(item->data[pos]));
	i = pos;
	while (item->data[i + 1])
	{
		item->data[i] = ft_strdup(item->data[i + 1]);
		free(item->data[i + 1]);
		i += 1;
	}
	item->data[i] = NULL;
}

int				array_find(int hashkey, char *var)
{
	int		i;
	char	*parsed;
    t_hashmap  *item;

	i = 0;
    item = hash_search(hashkey, g_shell);
	while (item->data[i])
	{
		parsed = ft_strsub(item->data[i], 0, ft_lfind(item->data[i], '='));
		if (ft_strequ(parsed, var))
		{
			free(parsed);
			return (i);
		}
		free(parsed);
		i += 1;
	}
	return (i);
}

char			*array_get(int hashkey, char *var)
{
	int		i;
	char	*parsed;
    t_hashmap  *item;

	i = 0;
    item = hash_search(hashkey, g_shell);
	while (item->data[i])
	{
		parsed = ft_strsub(item->data[i], 0, ft_lfind(item->data[i], '='));
		if (ft_strequ(parsed, var))
		{
			free(parsed);
			return (ft_strchr(item->data[i], '=') + 1);
		}
		free(parsed);
		i += 1;
	}
	return (NULL);
}

void            array_set(int hashkey, char *key, char *val)
{
	int		i;
	char	*tmp;
    t_hashmap  *item;

    item = hash_search(hashkey, g_shell);
	tmp = ft_strjoin(key, "=");
	i = array_find(hashkey, key);
	if (item->data[i])
	{
		ft_strdel(&item->data[i]);
		if (val)
			item->data[i] = ft_strjoin(tmp, val);
		else
			item->data[i] = ft_strdup(tmp);
	}
	else
	{
		item->data = array_realloc(item->data, i + 1);
		if (val)
			item->data[i] = ft_strjoin(tmp, val);
		else
			item->data[i] = ft_strdup(tmp);
	}
	free(tmp);
}
