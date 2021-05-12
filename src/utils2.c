/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:23:05 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/12 09:26:18 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_char(int c)
{
	return (write(0, &c, 1));
}

char			**array_realloc(char **arr, size_t size)
{
	int		i;
	char	**new;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (arr[i] && i < (int)(size - 1))
	{
		if (!(new[i] = ft_strdup(arr[i])))
			return (NULL);
		free(arr[i]);
		i++;
	}
	new[size] = NULL;
	free(arr);
    arr = NULL;
	return (new);
}
