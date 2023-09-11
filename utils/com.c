/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:15:37 by coder             #+#    #+#             */
/*   Updated: 2023/08/26 08:16:19 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all_paths(char **all_paths)
{
	char	**ptr;

	if (all_paths)
	{
		ptr = all_paths;
		while (*ptr)
		{
			free(*ptr);
			ptr++;
		}
		free(all_paths);
	}
}

char	*access_all_paths(char **all_paths)
{
	char	**ptr;

	ptr = all_paths;
	while (*ptr)
	{
		if (access(*ptr, F_OK | X_OK) == 0)
			return (ft_strdup(*ptr));
		ptr++;
	}
	return (NULL);
}

int	get_path_index_from_envp(char **envp)
{
	char	**ptr;
	int		index;

	ptr = envp;
	index = 0;
	while (*ptr)
	{
		if (ft_strncmp(*ptr, "PATH=", 5) == 0)
			return (index);
		ptr++;
		index++;
	}
	return (-1);
}

char	*get_path(const char *cmd_arg, char **envp)
{
	int		i;
	char	**all_paths;
	char	*paths;

	if (cmd_arg[0] == '.')
		return (strdup(cmd_arg));
	i = get_path_index_from_envp(envp);
	if (i == -1)
	{
		write(2, "Error getting path index from ENVP\n", 35);
		return (NULL);
	}
	all_paths = cat_cmd_to_all_paths(cmd_arg, ft_split(envp[i] + 5, ':'));
	if (!all_paths)
		return (NULL);
	paths = access_all_paths(all_paths);
	free_all_paths(all_paths);
	return (paths);
}
