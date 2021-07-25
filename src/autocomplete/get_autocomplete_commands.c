/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_autocomplete_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 17:02:30 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/07/25 11:56:30 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "autocomplete.h"

#include <dirent.h>

void	copy_and_escape_characters(char *dst, char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (!filename_character_allowed(src[i]))
		{
			dst[i + j] = '\\';
			j++;
		}
		dst[i + j] = src[i];
		i++;
	}
}

t_autocomp	*autocomp_new_command(char *command)
{
	t_autocomp	*autocomp;

	autocomp = (t_autocomp *)ft_memalloc(sizeof(t_autocomp));
	copy_and_escape_characters(autocomp->command, command);
	return (autocomp);
}

void	autocomp_append_command(char *command, t_shell *shell)
{
	if (!shell->autocomp)
	{
		shell->autocomp = autocomp_new_command(command);
		shell->autocomp_tail = shell->autocomp;
	}
	else
	{
		shell->autocomp_tail->next = autocomp_new_command(command);
		shell->autocomp_tail = shell->autocomp_tail->next;
	}
}

void	autocomp_commands_append_dir(char *path, t_shell *shell)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;

	p_dir = opendir(path);
	if (!p_dir)
		return ;
	while (1)
	{
		p_dirent = readdir(p_dir);
		if (!p_dirent)
			break ;
		if (!ft_strequ(p_dirent->d_name, ".")
			&& !ft_strequ(p_dirent->d_name, ".."))
			autocomp_append_command(p_dirent->d_name, shell);
	}
	closedir(p_dir);
}

void	autocomplete_from_path(t_shell *shell)
{
	char	**paths;
	int		i;

	paths = ft_strsplit(getenv("PATH"), ':');
	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		autocomp_commands_append_dir(paths[i++], shell);
	while (i >= 0)
		free(paths[i--]);
	free(paths);
}

void	free_autocomp_commands(t_shell *shell)
{
	t_autocomp	*cur;
	t_autocomp	*tmp;

	cur = shell->autocomp;
	shell->autocomp = NULL;
	shell->autocomp_tail = NULL;
	while (cur)
	{
		tmp = cur;
		cur = tmp->next;
		free(tmp);
	}
}

void	get_autocomplete_commands(t_shell *shell)
{
	free_autocomp_commands(shell);
	autocomp_commands_append_dir(".", shell);
	autocomplete_from_path(shell);
}
