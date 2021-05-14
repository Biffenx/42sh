/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:54:42 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/14 15:22:07 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

/*
** https://www.man7.org/linux/man-pages/man1/cd.1p.html
*/

static int	move_to(char *path, int print)
{
	char	*pwd;
	char	cwd[PATH_MAX];
	struct stat stats;
	char *buf = NULL;

	ft_printf("%s ", path);
	readlink(path, buf, PATH_MAX);
	ft_printf("%s\n", buf);
	pwd = getenv("PWD");
	// if (stat(path, &stats) != -1)
	// 	ft_printf("%s\n", S_ISLNK(stats.st_mode));
	if (!chdir(path))
	{
		setenv("OLDPWD", pwd, 1);
		setenv("PWD", getcwd(cwd, PATH_MAX), 1);
		if (print)
			ft_putendl(cwd);
		return (0);
	}
	if (stat(path, &stats) == -1)
		print_error(NOT_FOUND_ERR, path);
	else if (!S_ISDIR(stats.st_mode))
		print_error(NOT_DIR_ERR, path);
	else if (access(path, R_OK) == -1)
		print_error(PERMISSION_ERR, path);
	return (1);
}

/*
**		Built-in cd command.
*/

int	cd_builtin(char **argv)
{

	if (argv[1] && argv[2] && ft_strequ(argv[1], "-"))
	{
		write(2, "42sh: cd: too many arguments\n", 30);
		return (1);
	}	
	if (!argv[1])
		return (move_to(getenv("HOME"), 0));
	else if (ft_strchr(&argv[1][0], '-'))
	{		
		if ((ft_strequ(argv[1], "-L") && argv[2]))
			return (move_to(argv[2], 0));
		else
			return (move_to(getenv("OLDPWD"), 1));
	}
	else if (ft_strequ(argv[1], "--"))
		return (move_to(getenv("HOME"), 0));
	else
		return (move_to(argv[1], 0));
}
