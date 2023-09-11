/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:24:07 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 14:35:12 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_home(char *path, t_config *data)
{
	char	*home;

	if (path[0] != '~' && path[0] != '-')
		return (ft_strdup(path));
	if (path[0] == '-')
		return (get_env_value(data->env, "OLDPWD"));
	home = get_home_dir_from_envs(data);
	return (ft_strjoin(home, path + 1));
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		i++;
	}
	return (i);
}

char	*get_home_dir_from_envs(t_config *data)
{
	t_env	*temp;

	temp = data->env;
	while (temp)
	{
		if (!ft_strncmp (temp->key, "HOME", 4))
		{
			if (ft_strlen(temp->value) > PATH_MAX)
			{
				write (2, "cd: HOME too big to fit in here\n", 17);
				data->exit_code = 1;
				return (NULL);
			}
			return (temp->value);
		}
		temp = temp->next;
	}
	data->exit_code = 1;
	return (NULL);
}

int	cd_error_args(t_config *data)
{
	ft_putstr_fd("cd: too many arguments\n", 2);
	data->exit_code = 1;
	return (data->exit_code);
}
