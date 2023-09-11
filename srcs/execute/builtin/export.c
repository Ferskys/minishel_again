/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 00:12:17 by viferrei          #+#    #+#             */
/*   Updated: 2023/09/10 17:53:54 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	equal_found(char *str, t_config *data)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '=')
			return (1);
		else if (!is_variable(*str))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			data->exit_code = 1;
			return (0);
		}
		str++;
	}
	return (0);
}

static int	has_letter(const char *str)
{
	while (*str && *str != '=')
	{
		if (!isalpha(*str))
			return (1);
		str++;
	}
	return (0);
}

static void	process_arguments(char **args, t_com *com, t_config *data)
{
	char	*key;
	char	*value;
	int		valid_input;

	valid_input = 0;
	args++;
	while (*args)
	{
		if (has_letter(*args) || ((ft_strlen(*args) < 3) && !valid_input))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			data->exit_code = 1;
			return ;
		}
		if (equal_found(*args, data))
		{
			key = ft_strtok(*args, "=");
			value = ft_strtok(NULL, "=");
			set_env(&data->env, key, value);
			free_char_array(com->envp);
			com->envp = tok_envp(data->env);
			valid_input = 1;
		}
		args++;
	}
}

int	builtin_export(char **args, t_com *com, t_config *data)
{
	if (!args[1])
	{
		print_export_list(data->env);
		return (data->exit_code);
	}
	process_arguments(args, com, data);
	return (data->exit_code);
}
