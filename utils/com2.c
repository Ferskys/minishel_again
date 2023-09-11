/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 08:15:44 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/26 08:26:43 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_all_paths(char **all_paths)
{
	int		all_paths_count;
	char	**ptr;

	all_paths_count = 0;
	ptr = all_paths;
	while (*ptr)
	{
		all_paths_count++;
		ptr++;
	}
	return (all_paths_count);
}

char	*create_command(const char *cmd_arg, const char *path)
{
	int		len;
	char	*result;

	len = strlen(path) + strlen(cmd_arg) + 2;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, path, len);
	ft_strlcat(result, "/", len);
	ft_strlcat(result, cmd_arg, len);
	return (result);
}

char	**cat_cmd_to_all_paths(const char *cmd_arg, char **all_paths)
{
	int		all_paths_count;
	char	**result;
	char	**ptr;
	char	**result_ptr;

	all_paths_count = count_all_paths(all_paths);
	result = malloc(sizeof(char *) * (all_paths_count + 1));
	if (!result)
		return (NULL);
	ptr = all_paths;
	result_ptr = result;
	while (*ptr)
	{
		*result_ptr = create_command(cmd_arg, *ptr);
		if (!(*result_ptr))
		{
			free_all_paths(result);
			return (NULL);
		}
		ptr++;
		result_ptr++;
	}
	*result_ptr = NULL;
	return (result);
}
