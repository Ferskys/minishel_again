/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:48:16 by viferrei          #+#    #+#             */
/*   Updated: 2023/09/11 18:25:35 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	redirect_input(t_reds *in)
{
	int	fd;

	if (in->target && access(in->target, F_OK))
	{
		ft_putstr_fd(in->target, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	else if (in->target)
	{
		fd = open(in->target, O_RDONLY, FD_CLOEXEC);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	redirect_heredoc(int original_fds[2], t_com *cmd, t_config *data)
{
	char	*heredoc_file;
	int		fd;

	restore_original_fds(original_fds);
	heredoc_file = heredoc(cmd->red_in->target, data);
	if (!heredoc_file)
		return (1);
	fd = open(heredoc_file, O_RDONLY, FD_CLOEXEC);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(heredoc_file);
	free(heredoc_file);
	dup2(fd, STDOUT_FILENO);
	if (!cmd->command)
	{
		destroy_token_list(data);
		clear_env(data);
		rl_clear_history();
		close_inherited_fds();
		destroy_exec_info(cmd);
		exit(0);
	}
	return (0);
}

int	handle_input(t_com *cmd, int original_fds[2], t_config *data)
{
	t_reds	*in;

	in = cmd->red_in;
	if (!in)
		return (0);
	if (original_fds[0] == NO_REDIRECT)
		original_fds[0] = dup(STDIN_FILENO);
	while (in)
	{
		if (in->type == INFILE)
			if (redirect_input(in))
				return (1);
		if (in->type == HEREDOC)
			if (redirect_heredoc(original_fds, cmd, data))
				return (1);
		in = in->next;
	}
	return (0);
}

int	handle_redirects(t_com *cmd, int original_fds[2], t_config *data)
{
	if (handle_input(cmd, original_fds, data))
		return (1);
	handle_output(cmd->red_out, original_fds);
	return (0);
}
