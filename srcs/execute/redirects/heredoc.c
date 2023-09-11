/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:03:57 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 18:32:23 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	generate_a_random_name(char *random_name, char *seed)
{
	int		i;
	void	*ptr;

	i = ft_strlcpy(random_name, "/tmp/", PATH_MAX - 1);
	i += ft_strlcat(random_name, "datah", PATH_MAX - 1);
	i += ft_strlcat(random_name, seed, PATH_MAX - 1);
	ptr = malloc (1);
	if (!ptr)
		return (-1);
	free (ptr);
	ptr = ft_itoa((size_t) ptr);
	i += ft_strlcat(random_name, ptr, PATH_MAX - 1);
	free (ptr);
	if (i >= PATH_MAX)
	{
		write (2, "heredoc too big!\n", 17);
		return (-1);
	}
	return (i);
}

void	daddy_issues(int pid)
{
	int	i;

	if (pid)
	{
		ignore_signals();
		waitpid(pid, &i, 0);
		set_signal();
	}
}

char	*heredoc(char *target, t_config *data)
{
	int		ret_fd;
	int		pid;
	char	random_name[PATH_MAX];

	if (!target)
		return (0);
	generate_a_random_name(random_name, target);
	ret_fd = open (random_name, O_CREAT | O_TRUNC | O_DIRECTORY | O_RDWR, 0666);
	pid = fork();
	daddy_issues(pid);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		write_to_heredoc(ret_fd, target, data);
		close(ret_fd);
		data->issue_exit = -1;
		return (0);
	}
	close(ret_fd);
	return (ft_strdup(random_name));
}
