/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 08:39:00 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:31:43 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	create_child(void)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		write(2, "error: Can't spawn child\n", 25);
		exit(-1);
	}
	return (child_pid);
}

int	pipe_handle(t_config *data, t_com *cmd)
{
	if (cmd->receives_from_pipe)
	{
		close(data->pipe_in[1]);
		dup2(data->pipe_in[0], STDIN_FILENO);
	}
	if (cmd->sends_to_pipe)
	{
		close(data->pipe_out[0]);
		dup2(data->pipe_out[1], STDOUT_FILENO);
	}
	return (0);
}
