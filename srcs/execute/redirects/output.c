/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 08:50:03 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/11 00:56:44 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_output(t_reds *red_out, int original_fds[2])
{
	t_reds	*out;
	int		fd;

	out = red_out;
	if (!out)
		return (0);
	if (original_fds[1] == NO_REDIRECT)
		original_fds[1] = dup(STDOUT_FILENO);
	while (out)
	{
		if (access(out->target, W_OK) != 0)
		{
			perror(out->target);
			return (1);
		}
		if (out->type == OVERWRITE)
			fd = open(out->target, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (out->type == APPEND)
			fd = open(out->target, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
		{
			perror("open");
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		out = out->next;
	}
	return (0);
}
