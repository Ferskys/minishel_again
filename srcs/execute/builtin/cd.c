/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:13:35 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 14:33:17 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	cd_to_home(t_config *data)
{
	char	*home_path;
	char	curr_path[PATH_MAX];

	getcwd(curr_path, PATH_MAX);
	home_path = get_env_value(data->env, "HOME");
	if (home_path)
	{
		if (chdir(home_path))
		{
			write(2, "cd: something went terribly wrong\n", 34);
			return (2);
		}
		set_env(&data->env, "OLDPWD", curr_path);
		set_env(&data->env, "PWD", home_path);
		return (0);
	}
	write (2, "cd: HOME not set\n", 17);
	return (1);
}

static int	cd_to_path(char *path, t_config *data)
{
	char	curr_path[PATH_MAX];
	char	*print_err;

	getcwd(curr_path, PATH_MAX);
	if (!access(path, R_OK | F_OK))
	{
		if (chdir(path))
		{
			write(2, "cd: something went terribly wrong\n", 34);
			return (2);
		}
		set_env(&data->env, "OLDPWD", curr_path);
		getcwd(curr_path, PATH_MAX);
		set_env(&data->env, "PWD", curr_path);
		return (0);
	}
	print_err = ft_strjoin("cd: ", path);
	perror(print_err);
	free(print_err);
	return (1);
}

static int	cd_to_tilde(char **args, t_config *data)
{
	char	*expanded_path;

	expanded_path = expand_home(args[1], data);
	if (ft_strlen(expanded_path) > PATH_MAX)
	{
		expanded_path = safe_free (expanded_path);
		write (2, "cd: path too big to fit in here\n", 17);
		return (1);
	}
	data->exit_code = cd_to_path(expanded_path, data);
	expanded_path = safe_free (expanded_path);
	return (data->exit_code);
}

static int	cd_to_oldpwd(int print, t_config *data)
{
	char	oldcwd[PATH_MAX];
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = get_env_value(data->env, "OLDPWD");
	getcwd(oldcwd, PATH_MAX - 1);
	if (chdir(oldpwd))
	{
		write(2, "cd: can't go back to where you haven't been\n", 44);
		return (2);
	}
	if (print)
	{
		ft_putstr_fd(oldpwd, 1);
		write(1, "\n", 1);
	}
	getcwd(cwd, PATH_MAX -1);
	set_env(&data->env, "OLDPWD", oldcwd);
	set_env(&data->env, "PWD", cwd);
	return (0);
}

int	builtin_cd(char **args, char **envp, t_config *data)
{
	int		arg_number;

	(void) envp;
	arg_number = count_args(args);
	if (arg_number == 1)
		data->exit_code = cd_to_home(data);
	if (arg_number > 2)
		return (cd_error_args(data));
	if (arg_number == 2)
	{
		if (args[1][0] == '~' && args[1][1] != '-')
			data->exit_code = cd_to_tilde(args, data);
		else if (args[1][0] == '-' && !args[1][1])
			data->exit_code = cd_to_oldpwd(1, data);
		else if (args[1][0] == '~' && args[1][1] == '-')
			data->exit_code = cd_to_oldpwd(0, data);
		else if (args[1][0] == '-' && args[1][1])
		{
			write (2, "CD: No options allowed brah\n", 28);
			data->exit_code = 1;
		}
		else
			data->exit_code = cd_to_path(args[1], data);
	}
	return (data->exit_code);
}
