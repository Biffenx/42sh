/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:33:21 by vkuokka           #+#    #+#             */
/*   Updated: 2021/08/01 14:43:32 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**redirection to a file can either be truncate or append
*/

int redir_is_truncate(char c)
{
	if (c == '\0')
		return 1;
	else
		return 0;
}

int create_truncate_file(char *file)
{
	return (open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR));
}

int create_append_file(char *file)
{
	return (open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IROTH | S_IWGRP | S_IWUSR));
}
