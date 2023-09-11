/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 02:05:59 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 18:27:50 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	arg_is_number(char *arg)
{
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	builtin_exit(t_com *cmd, char **args, t_config *data)
{
	int	argc;

	argc = count_args(args);
	if (argc > 2 && atoll(args[1]))
	{
		data->exit_code = 1;
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (argc == 1)
		data->exit_code = data->exit_code;
	else if (args[1] && (!atoll(args[1]) || errno == ERANGE))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		data->exit_code = 2;
	}
	else if (args[1] && atoll(args[1]))
		data->exit_code = atoll(args[1]);
	if (!cmd->sends_to_pipe && !cmd->receives_from_pipe)
		data->issue_exit = 1;
	if (data->issue_exit)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	return ((unsigned char) data->exit_code);
}
