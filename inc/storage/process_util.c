/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hege <hege@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 12:40:32 by srouhe            #+#    #+#             */
/*   Updated: 2020/10/15 13:53:02 by hege             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int         get_cmd_size(t_token *token)
{
    int     i;

    i = 0;
    while (token && !(token->type & MASK_OP))
    {
        i++;
        token = token->next;
    }
    return (i);
}

char        **tokens_to_array(t_token **tokens)
{
    char    **r;
    int     i;
    int     size;

    i = 0;
    size = get_cmd_size(*tokens);
	if (!(r = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
    while (*tokens && !((*tokens)->type & MASK_OP) && !((*tokens)->type & MASK_REDIR))
    {
        // ft_printf("dupping token %s\n", (*tokens)->data);
        if ((*tokens)->type & IO_NUM || (*tokens)->type & T_BG)        {
            *tokens = (*tokens)->next;
            break ;
        }
        r[i] = ft_strdup((*tokens)->data);
        i++;
        *tokens = (*tokens)->next;
    }
    r[i] = NULL;
    return (r);
}

char         *proc_path(char *cmd)
{
	int				i;
	char			**path;
	char			*proc_path;
	struct stat		attr;

	i = 0;
	path = ft_strsplit(getenv("PATH"), ':');
	while (path && path[i])
	{
		proc_path = ft_pathjoin(path[i], cmd);
		if (!lstat(proc_path, &attr) && \
			!(!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, "..")))
		{
			ft_freestrarr(path);
			return (proc_path);
		}
		free(proc_path);
		i++;
	}
    return (NULL);
}