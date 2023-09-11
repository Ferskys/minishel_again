/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 00:53:10 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 14:35:22 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_oldpwd(t_config *data, char *curr_path)
{
	t_env	*ls_oldpwd;

	ls_oldpwd = data->env;
	while (ls_oldpwd)
	{
		if (!ft_strncmp (ls_oldpwd->key, "OLDPWD", 6))
			break ;
		ls_oldpwd = ls_oldpwd->next;
	}
	free(data->oldpwd);
	data->oldpwd = ft_strdup(curr_path);
	if (ls_oldpwd)
	{
		set_env(&data->env, "OLDPWD", curr_path);
		return (0);
	}
	return (1);
}

int	update_pwd(t_config *data, char *path)
{
	t_env	*temp;

	temp = data->env;
	while (temp)
	{
		if (!ft_strncmp(temp->key, "PWD", 3))
		{
			temp->value = safe_free(temp->value);
			temp->value = path;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
