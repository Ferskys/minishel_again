/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:45:04 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 18:27:22 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	builtin_pwd(char **args, char **envp, t_config *data)
{
	char	path_name[PATH_MAX];

	(void) args;
	(void) envp;
	if (!getcwd(path_name, PATH_MAX))
	{
		write (2, "Error: user is trying to fuck shit up!\n", 40);
		data->exit_code = 1;
		return (1);
	}
	printf("%s\n", path_name);
	return (0);
}
