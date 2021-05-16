/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_bcdef.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:46:57 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/05/16 21:47:11 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	flag_b_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFBLK));
}

int	flag_c_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFCHR));
}

int	flag_d_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFDIR));
}

int	flag_e_test(char *path)
{
	if (access(path, F_OK) == 0)
		return (0);
	return (1);
}

int	flag_f_test(char *path)
{
	struct stat		buf;

	if (stat(path, &buf) == -1)
		return (1);
	return (!((buf.st_mode & S_IFMT) == S_IFREG));
}
