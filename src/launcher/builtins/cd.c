/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilen <jwilen@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:54:42 by vkuokka           #+#    #+#             */
/*   Updated: 2021/05/29 14:44:01 by jwilen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

/*
** https://www.man7.org/linux/man-pages/man1/cd.1p.html
*/

static char	**parse_options(char **argv, int *options)
{
	int i;
	int	j;

	*options = 0;
	i = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'L')
				*options = 1 << 0;
			else if (argv[i][j] == 'P')
				*options = 1 << 1;
			j += 1;
		}
		i += 1;
	}
	return (argv + i);
}

static void ascent_path(char *path)
{
	size_t	i;

	i = ft_strlen(path);
	if (i > 1 && path[i - 1] == '/')
		path[i - 1] = 0;
	while (i > 1 && path[i] != '/')
		i -= 1;
	path[i] = '\0';
	ft_putendl(path);
}

static void	descent_path(char *path, char *data)
{
		if (path[ft_strlen(path) - 1] != '/')
			ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, data, PATH_MAX);
}

static char	*parse_path(int options, char *path, char *data)
{
	char	link[PATH_MAX];
	ssize_t	ret;

	ft_bzero(path, PATH_MAX);
	if (*data == '/')
		ft_strlcat(path, data, PATH_MAX);
	else
	{
		ft_strlcat(path, getenv("PWD"), PATH_MAX);
		if (ft_strequ(data, ".."))
			ascent_path(path);
		else if (!ft_strequ(data, "."))
			descent_path(path, data);
	}
	if (options & 1 << 1)
	{
		ret = readlink(path, link, PATH_MAX);
		if (ret == -1)
			return (path);
		path[ret] = 0;
		ft_bzero(path, PATH_MAX);
		ft_strlcat(path, link, PATH_MAX);
	}
	return (path);
}

static int	move_to(char *path, int print)
{
	char	*pwd;
	struct stat stats;

	pwd = getenv("PWD");
	if (!chdir(path))
	{
		setenv("OLDPWD", pwd, 1);
		setenv("PWD", path, 1);
		if (print)
			ft_putendl(path);
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
	int options;
	char	path[PATH_MAX];

	argv = parse_options(argv, &options);
	if (argv[0] && argv[1])
		ft_dprintf(STDERR_FILENO, STR_ARG_ERR, "cd");
	if (!argv[0])
		return (move_to(getenv("HOME"), 0));
	else if (ft_strequ(argv[0], "-"))
		return (move_to(getenv("OLDPWD"), 1));
	else if (ft_strequ(argv[0], "--"))
		return (move_to(getenv("HOME"), 0));
	else
		return (move_to(parse_path(options, path, argv[0]), 0));
	return (1);
}
