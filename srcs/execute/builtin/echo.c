/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 03:55:52 by viferrei          #+#    #+#             */
/*   Updated: 2023/09/10 19:02:48 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	should_skip_newline(char **args)
{
	if (!args[1])
		return (1);
	if (!ft_strcmp(args[1], "-n"))
		return (0);
	return (1);
}

void	print_echo_output(char **args)
{
	int	i;

	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (args[i])
		ft_putstr_fd(args[i], STDOUT_FILENO);
}

int	builtin_echo(char **args)
{
	int	newline;

	newline = should_skip_newline(args);
	print_echo_output(args);
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
