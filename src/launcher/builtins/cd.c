/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochumwilen <jochumwilen@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:54:42 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/16 18:49:41 by jochumwilen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

/*
** https://www.man7.org/linux/man-pages/man1/cd.1p.html
*/

/*
** Testing ZSH vs 42sh cd command with or without flags
**(S) is a symbolic link directory
**
** ZSH(S):	cd home | PWD=/home OLDPWD=/
** 42(S):	cd home | PWD=/home OLDPWD=/
** ZSH:		cd bin | PWD=/bin OLDPWD=/
** 42:		cd bin | PWD=/bin OLDPWD=/
** ZSH: 	cd school | PWD=/Users/jochumwilen/school OLDPWD=/Users/jochumwilen
** 42:		cd school | PWD=/Users/jochumwilen/School OLDPWD=/Users/jochumwilen
** ZSH(S): 	cd s_github | PWD=/Users/jochumwilen/School/s_github OLDPWD=/Users/jochumwilen/School
** 42(S):	cd s_github | PWD=/Users/jochumwilen/School/s_github OLDPWD=/Users/jochumwilen/School
**
** ZSH(S): 	cd -L home | PWD=/home OLDPWD=/
** 42(S):	cd -L home | PWD=/home OLDPWD=/
** ZSH:		cd -L bin | PWD=/bin OLDPWD=/
** 42:		cd -L bin | PWD=/bin OLDPWD=/
** ZSH: 	cd -L school | PWD=/Users/jochumwilen/school OLDPWD=/Users/jochumwilen
** 42:		cd -L school | PWD=/Users/jochumwilen/School OLDPWD=/Users/jochumwilen
** ZSH(S): 	cd -L s_github | PWD=/Users/jochumwilen/School/s_github OLDPWD=/Users/jochumwilen/School
** 42(S):	cd -L s_github | PWD=/Users/jochumwilen/School/s_github OLDPWD=/Users/jochumwilen/School

**
** ZSH(S): 	cd -P home | PWD=/System/Volumes/Data/home OLDPWD=/
** 42(S):	cd -P home | PWD=/System/Volumes/Data/home OLDPWD=/
** ZSH:		cd -P bin | PWD=/bin OLDPWD=/
** 42:		cd -P bin | PWD=/bin OLDPWD=/
** ZSH: 	cd -P school | PWD=/Users/jochumwilen/school OLDPWD=/Users/jochumwilen
** 42:		cd -P school | PWD=/Users/jochumwilen/School OLDPWD=/Users/jochumwilen
** ZSH(S): 	cd -P s_github | PWD=/Users/jochumwilen/Github OLDPWD=/Users/jochumwilen/School
** 42(S):	cd -P s_github | PWD=/Users/jochumwilen/Github OLDPWD=/Users/jochumwilen/School/

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
	char		buf[PATH_MAX];
	ssize_t		len;
	char		*tmp;

	len = -1;
	pwd = getenv("PWD");
	if (!ft_strequ(pwd, "/"))
		tmp = ft_strjoin(pwd, "/");
	tmp = ft_strjoin(pwd, path);
	len = readlink(tmp, buf, sizeof(buf) - 1);
	if (len != -1)
	{
		buf[len] = '\0';
		path = buf;
	}
	if (!chdir(path))
	{
		if (!ft_strnequ(path, "/", 1))
			path = ft_strjoin("/", path);
		setenv("OLDPWD", pwd, 1);
		setenv("PWD", path, 1);
	}
	if (len != -1)
		cd_stat_error(path);
	else
		cd_stat_error(tmp);
	return (1);
}

static int		move_to(char *path, int print)
{
	char		*pwd;
	struct stat stats;
	char		abspath[PATH_MAX];
	char		*tmp;

	pwd = getenv("PWD");
	lstat(path, &stats);
	getcwd(abspath, PATH_MAX);
	tmp = ft_strrchr(abspath, '/');
	if (!chdir(path))
	{
		if (S_ISLNK(stats.st_mode))
		{
			setenv("OLDPWD", abspath, 1);
			if (!ft_strequ(abspath, "/"))
				tmp = ft_strcat(abspath, "/");
			setenv("PWD", ft_strcat(tmp, path), 1);
		}
		else
		{
			setenv("OLDPWD", abspath, 1);
			setenv("PWD", getcwd(tmp, PATH_MAX), 1);
		}
		if (print)
			ft_putendl(pwd);
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
		else if ((ft_strequ(argv[1], "--") || (ft_strequ(argv[1], "-P")
		&& !argv[2])) || (ft_strequ(argv[1], "-L") && !argv[2]))
			return (move_to(getenv("HOME"), 0));
		else if (ft_strequ(argv[1], "-"))
			return (move_to(getenv("OLDPWD"), 1));
		else
		{
			write(2, "43sh: cd: no such file or directory\n", 36);
			return (1);
		}
	}
	else
		return (move_to(argv[1], 0));
}
