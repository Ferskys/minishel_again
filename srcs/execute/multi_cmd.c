/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 23:19:44 by viferrei          #+#    #+#             */
/*   Updated: 2023/09/11 01:19:04 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	swap_pipes(t_config *data)
{
	static int	init;

	if (!init)
	{
		pipe(data->pipe_out);
		init++;
	}
	data->pipe_in[0] = data->pipe_out[0];
	data->pipe_in[1] = data->pipe_out[1];
	pipe(data->pipe_out);
	return (0);
}

int	exec_multi(t_com *cmd, t_config *data, int original_fds[2])
{
	int	control;

	if (original_fds[0] == NO_REDIRECT)
		original_fds[0] = dup(STDIN_FILENO);
	if (original_fds[1] == NO_REDIRECT)
		original_fds[1] = dup(STDOUT_FILENO);
	swap_pipes(data);
	control = cmd->sends_to_pipe;
	if (data->issue_exit)
		return (data->issue_exit);
	if (cmd->is_builtin)
		data->exit_code = exec_fork_builtin(cmd, data, original_fds);
	else
		data->exit_code = exec_com_multi(cmd, data, original_fds);
	return (control);
}
