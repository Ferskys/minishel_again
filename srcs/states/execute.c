/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:49:30 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/13 16:41:32 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	create_redirect_files(t_com *cmd)
{
	t_reds	*tmp;

	tmp = cmd->red_out;
	while (tmp)
	{
		open(tmp->target, O_CREAT, 0777);
		tmp = tmp->next;
	}
}

static int	validate_redirects(t_com *cmd)
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

static int	exec_loop(t_com *cmd, t_config *data, int original_fds[2])
{
	if (!cmd)
		return (0);
	if (cmd->block_exec)
	{
		write(2, cmd->error_to_print, ft_strlen(cmd->error_to_print));
		return (0);
	}
	create_redirect_files(cmd);
	if (!cmd->receives_from_pipe && !cmd->sends_to_pipe)
	{
		if (validate_redirects(cmd))
			return (0);
		exec_one_cmd(cmd, data, original_fds);
		return (0);
	}
	else if (!data->issue_exit)
		return (exec_multi(cmd, data, original_fds));
	return (1);
}

static void	execute_command_loop(t_config *data, int *original_fds)
{
	t_com	*cmd;
	int		control;

	control = 1;
	while (control)
	{
		cmd = get_exec_info(data);
		control = exec_loop(cmd, data, original_fds);
		destroy_exec_info(cmd);
		if (data->issue_exit)
			break ;
	}
}

static void	execute_post_loop(t_config *data, int *original_fds)
{
	while (wait(&data->exit_code) > 0)
		continue ;
	if (data->exit_code >= 256)
		data->exit_code = data->exit_code >> 8;
	set_signal();
	clear_data(data);
	restore_original_fds(original_fds);
	if (data->issue_exit)
		data->state = EXIT;
	if (data->state == EXECUTE)
		data->state = PROMPT;
}

void	execute(void)
{
	t_config	*data;
	int			original_fds[2];

	original_fds[0] = NO_REDIRECT;
	original_fds[1] = NO_REDIRECT;
	data = get_data();
	ignore_signals();
	execute_command_loop(data, original_fds);
	execute_post_loop(data, original_fds);
}
