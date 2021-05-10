/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:54:42 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/10 22:16:01 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

static int	move_to(char *path, int print)
{
	char	*pwd;
	char	cwd[PATH_MAX];
	struct stat stats;
	

	pwd = getenv("PWD");
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

	if (argv[1] && argv[2])
	{
		write(2, "42sh: cd: too many arguments", 29);
		return (1);
	}	
	if (!argv[1])
		return (move_to(getenv("HOME"), 0));
	else if (ft_strequ(argv[1], "-"))
		return (move_to(getenv("OLDPWD"), 1));
	else if (ft_strequ(argv[1], "--"))
		return (move_to(getenv("HOME"), 0));
	else
		return (move_to(argv[1], 0));
}
