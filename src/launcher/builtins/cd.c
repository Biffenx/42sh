/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:54:42 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/15 22:39:55 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

/*
** https://www.man7.org/linux/man-pages/man1/cd.1p.html
*/

static void		cd_stat_error(char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == -1)
		print_error(NOT_FOUND_ERR, path);
	else if (!S_ISDIR(stats.st_mode))
		print_error(NOT_DIR_ERR, path);
	else if (access(path, R_OK) == -1)
		print_error(PERMISSION_ERR, path);
}

static int		move_to_flag_p(char *path)
{
	char		*pwd;
	char		buf[1024];
	ssize_t		len;
	char		*tmp;

	len = 0;
	pwd = getenv("PWD");
	if (!ft_strequ(pwd, "/"))
		tmp = ft_strcat(pwd, "/");
	tmp = ft_strcat(pwd, path);
	len = readlink(tmp, buf, sizeof(buf) - 1);
	if (len != -1)
	{
		buf[len] = '\0';
		path = buf;
	}
	if (!chdir(path))
	{
		setenv("OLDPWD", pwd, 1);
		setenv("PWD", path, 1);
	}
	cd_stat_error(path);
	return (1);
}

static int		move_to(char *path, int print)
{
	char		*pwd;
	char		cwd[PATH_MAX];
	struct stat stats;
	char		abspath[PATH_MAX];

	pwd = getenv("PWD");
	if (!chdir(path))
	{
		getcwd(abspath, PATH_MAX);
		path = ft_strrchr(abspath, '/');
		lstat(path, &stats);
		setenv("OLDPWD", pwd, 1);
		if (S_ISLNK(stats.st_mode))
			setenv("PWD", path, 1);
		else
			setenv("PWD", getcwd(cwd, PATH_MAX), 1);
		if (print)
			ft_putendl(cwd);
		return (0);
	}
	cd_stat_error(path);
	return (1);
}

static int		cd_argv_check(char **argv)
{
	if (argv[1] && argv[2] && !ft_strnequ(argv[1], "-", 1))
	{
		write(2, "42sh: cd: too many arguments\n", 30);
		return (1);
	}
	return (0);
}

/*
**		Built-in cd command.
*/

int				cd_builtin(char **argv)
{
	if (cd_argv_check(argv))
		return (1);
	if (!argv[1])
		return (move_to(getenv("HOME"), 0));
	else if (ft_strchr(&argv[1][0], '-'))
	{
		if ((ft_strequ(argv[1], "-P") && argv[2]))
			return (move_to_flag_p(argv[2]));
		else if ((ft_strequ(argv[1], "-L") && argv[2]))
			return (move_to(argv[2], 0));
		else if (ft_strequ(argv[1], "--"))
			return (move_to(getenv("HOME"), 0));
		else if ((ft_strequ(argv[1], "-P") && !argv[2])
		|| (ft_strequ(argv[1], "-L") && !argv[2]))
			return (move_to(getenv("HOME"), 0));
		else if (ft_strequ(argv[1], "-"))
			return (move_to(getenv("OLDPWD"), 1));
		else
		{
			write(2, "42sh: cd: no such file or directory\n", 36);
			return (1);
		}
	}
	else
		return (move_to(argv[1], 0));
}
