/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:44:00 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/14 10:46:50 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_redirect_files(t_com *cmd)
{
	t_reds	*tmp;

	tmp = cmd->red_out;
	while (tmp)
	{
		open(tmp->target, O_CREAT, 0777);
		tmp = tmp->next;
	}
}

int	validate_redirects(t_com *cmd)
{
	t_reds		*tmp;
	struct stat	sb;
	t_config	*data;

	data = get_data();
	tmp = cmd->red_out;
	while (tmp)
	{
		if (stat(tmp->target, &sb) == -1)
		{
			perror(tmp->target);
			data->exit_code = 1;
			return (1);
		}
		else if (access(tmp->target, W_OK) != 0)
		{
			perror(tmp->target);
			data->exit_code = 1;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
