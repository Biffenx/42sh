/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_glprs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:03:38 by jwilen            #+#    #+#             */
/*   Updated: 2021/05/22 12:45:24 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	flag_g_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (0);
	/* error: bitwise comparison always evaluates to false [-Werror=tautological-compare]
	return (!((buf.st_mode & S_IFMT) == S_ISGID));*/
}

int	flag_cap_l_test(char *path)
{
	struct stat		buf;

	if (lstat(path, &buf) == -1)
		return (1);
	return (!(S_ISLNK(buf.st_mode)));
}

int	flag_p_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFIFO));
}

int	flag_r_test(char *path)
{
	if (access(path, R_OK) == 0)
		return (0);
	return (1);
}

int	flag_cap_s_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFSOCK));
}
