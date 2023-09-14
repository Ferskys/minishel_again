/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 21:48:16 by viferrei          #+#    #+#             */
/*   Updated: 2023/09/14 19:03:09 by aqueiroz         ###   ########.fr       */
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

int	handle_input(t_com *cmd, int original_fds[2])
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
		in = in->next;
	}
	return (0);
}

int	handle_redirects(t_com *cmd, int original_fds[2])
{
	if (handle_input(cmd, original_fds))
		return (1);
	handle_output(cmd->red_out, original_fds);
	return (0);
}
