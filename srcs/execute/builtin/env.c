/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:50:18 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 14:33:32 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_for_path(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	if (!env_list)
	{
		write (2, "Y u env when no env?\n", 21);
		return (127);
	}
	while (temp)
	{
		if (!ft_strncmp(temp->key, "PATH", 4))
			break ;
		temp = temp->next;
	}
	if (!temp)
	{
		write(2, "env: No such file or directory\n", 31);
		return (127);
	}
	return (0);
}

int	builtin_env(char **args, char **envp, t_env *env_list)
{
	int			rc;

	(void) args;
	(void) envp;
	rc = check_for_path(env_list);
	if (rc)
		return (rc);
	print_env(env_list);
	return (0);
}
