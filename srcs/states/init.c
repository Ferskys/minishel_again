/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:09:21 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/14 10:25:53 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init(void)
{
	extern char	**environ;
	t_config	*data;
	char		*pwd;

	data = get_data();
	set_signal();
	data->env = create_env_list(environ);
	pwd = getcwd(NULL, 0);
	set_env(&data->env, "PWD", pwd);
	free(pwd);
	if (data->state == INIT)
		data->state = PROMPT;
}
