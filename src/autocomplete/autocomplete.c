/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:01:14 by jochumwilen       #+#    #+#             */
/*   Updated: 2021/06/03 22:34:41 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "autocomplete.h"
#include <dirent.h>

int	filename_character_allowed(char c)
{
	if (!ft_isprint(c))
		return (1);
	if (ft_isalnum(c))
		return (1);
	return (c == '-' || c == '_' || c == '.');
}

char	*ft_strdup_and_escape_characters(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
		if (!filename_character_allowed(str[i++]))
			j++;
	new_str = (char *)ft_memalloc(i + j + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!filename_character_allowed(str[i]))
		{
			new_str[i + j] = '\\';
			j++;
		}
		new_str[i + j] = str[i];
		i++;
	}
	return (new_str);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	len = 0;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	str = (char *)ft_memalloc(len + 1);
	if (!str)
		return (NULL);
	if (s1)
		ft_strcpy(str, s1);
	if (s2)
		ft_strcat(str, s2);
	free(s1);
	free(s2);
	return (str);
}

char	*join_path_and_filename(char *path, struct dirent *p_dirent)
{
	char	*tmp;

	if (ft_strequ(path, "."))
		tmp = NULL;
	else
	{
		tmp = ft_strdup(path);
		if (ft_strrchr(path, '/'))
			*ft_strrchr(tmp, '/') = '\0';
		tmp = ft_strjoinfree(tmp, ft_strdup("/"));
	}
	tmp = ft_strjoinfree(tmp,
	ft_strdup_and_escape_characters(p_dirent->d_name));
	if (p_dirent->d_type == DT_DIR)
		tmp = ft_strjoinfree(tmp, ft_strdup("/"));
	return (tmp);
}

int	match_with_input_after_slash(char *path, char *command)
{
	char	*tmp;

	tmp = ft_strrchr(path, '/');
	if (tmp)
	{
		tmp++;
		return (ft_strnequ(tmp, command, ft_strlen(tmp)));
	}
	return (1);
}

void	get_dir_commands_ext(struct dirent	*p_dirent, char *path,
		char **commands, int size)
{
	char	**tmp;

	if (match_with_input_after_slash(path, p_dirent->d_name) && !ft_strequ
		(p_dirent->d_name, ".") && !ft_strequ(p_dirent->d_name, ".."))
	{
		tmp = commands;
		commands = (char **)ft_memalloc(sizeof(char *) * (size + 1));
		if (tmp)
			ft_memcpy(commands, tmp, size * sizeof(char *));
		commands[size++ - 1] = join_path_and_filename(path, p_dirent);
	}
}

int	check_command_valid_dir(char *command)
{
	DIR		*p_dir;
	char	*tmp;

	if (ft_strrchr(command, '/'))
	{
		tmp = ft_strdup(command);
		*(ft_strrchr(tmp, '/') + 1) = '\0';
	}
	else
		tmp = ft_strdup(command);
	p_dir = opendir(tmp);
	if (!p_dir)
	{
		free(tmp);
		return (0);
	}
	closedir(p_dir);
	free(tmp);
	return (1);
}

DIR	*open_dir_until_last_slash(char *path)
{
	DIR		*p_dir;
	char	*tmp;

	p_dir = opendir(path);
	if (p_dir)
		return (p_dir);
	if (ft_strrchr(path, '/'))
	{
		tmp = ft_strdup(path);
		*(ft_strrchr(tmp, '/') + 1) = '\0';
	}
	else
		tmp = ft_strdup(path);
	p_dir = opendir(tmp);
	free(tmp);
	return (p_dir);
}

char	**get_dir_commands(char *path)
{
	DIR				*p_dir;
	struct dirent	*p_dirent;
	char			**commands;
	char			**tmp;
	int				size;

	if (!(p_dir = open_dir_until_last_slash(path)))
		exit(1);
	commands = NULL;
	size = 1;
	while ((p_dirent = readdir(p_dir)))
	{
		if (match_with_input_after_slash(path, p_dirent->d_name) &&
		!ft_strequ(p_dirent->d_name, ".") && !ft_strequ(p_dirent->d_name, ".."))
		{
			tmp = commands;
			commands = (char**)ft_memalloc(sizeof(char*) * (size + 1));
			if (tmp)
				ft_memcpy(commands, tmp, size * sizeof(char*));
			commands[size++ - 1] = join_path_and_filename(path, p_dirent);
		}
	}
	closedir(p_dir);
	return (commands);
}

int	loop_autocomplete(char *part_command, t_shell *shell)
{
	t_autocomp	*cur;
	int			i;

	i = 0;
	cur = shell->autocomp;
	while (cur)
	{
		if (ft_strnequ(cur->command, part_command, ft_strlen(part_command)))
			i++;
		cur = cur->next;
	}
	return (i);
}


char	**get_matching_commands(char *part_command, t_shell *shell)
{
	char		**matching_commands;
	t_autocomp	*cur;
	int			i;

	i = 0;
	cur = shell->autocomp;
	while (cur)
	{
		if (ft_strnequ(cur->command, part_command, ft_strlen(part_command)))
			i++;
		cur = cur->next;
	}
	if (!i)
		return (NULL);
	if (!(matching_commands = ft_memalloc(sizeof(char*) * (i + 1))))
		exit(1);
	i = 0;
	cur = shell->autocomp;
	while (cur)
	{
		if (ft_strnequ(cur->command, part_command, ft_strlen(part_command)))
			matching_commands[i++] = cur->command;
		cur = cur->next;
	}
	return (matching_commands);
}

char	*get_partial_command(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line) - 1;
	i = len;
	while (i >= 0 && line[i] != ' ')
		i--;
	return (ft_strsub(line, i + 1, len - i));
}

int	find_start_of_command_index(char *str, int end_index)
{
	while (end_index >= 0)
	{
		if (str[end_index] == ' ')
			if (end_index > 0 && str[end_index - 1] != '\\')
				break ;
		end_index--;
	}
	return (end_index);
}

void	complete_command(t_shell *shell , char previous_pressed_key,
char **matching_commands)
{
	char		*final_string;
	int			i;
	int			len;
	static int	j;

	if (!matching_commands || !(*matching_commands))
		return ;
	if (previous_pressed_key != TAB)
		j = 0;
	len = ft_strlen(shell->editor.buffer) - 1;
	i = len;
	i = find_start_of_command_index(shell->editor.buffer, i);
	final_string = ft_strjoinfree(ft_strsub(shell->editor.buffer, 0, i + 1),
			ft_strdup(matching_commands[j]));
	if (!matching_commands[j] || !matching_commands[j + 1])
		j = 0;
	else
		j = j + 1;
	ft_strcpy(shell->editor.buffer, final_string);
	shell->editor.cursor = ft_strlen(shell->editor.buffer);
}

void	autocomplete(t_shell *shell)
{
	static char		*partial_command = NULL;
	static char		**matching_commands = NULL;

	if (shell->prev_key_pressed != TAB)
	{
		free(partial_command);
		free(matching_commands);
		partial_command = get_partial_command(shell->editor.buffer);
		if (partial_command[0] == '\0')
			matching_commands = get_dir_commands(".");
		else if (check_command_valid_dir(partial_command))
			matching_commands = get_dir_commands(partial_command);
		else
		{
			matching_commands = get_matching_commands(partial_command, shell);
			ft_printf("mc3: %s\n", matching_commands);
		}
	}
	complete_command(shell, shell->prev_key_pressed, matching_commands);
}
