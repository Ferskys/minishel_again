/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:13:26 by aqueiroz          #+#    #+#             */
/*   Updated: 2023/09/14 11:27:50 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_var_name(char *str)
{
	char	var_name[100];
	int		i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	return (ft_strdup(var_name));
}

static char	*create_placeholder(void)
{
	char	*placeholder;

	placeholder = malloc(4000);
	placeholder[0] = '\0';
	return (placeholder);
}

static void	process_variable(char **input_ptr, char **placeholder_ptr,
		t_env *env_data)
{
	char	*var_name;
	char	*var_value;

	if (!find_variable(*input_ptr))
	{
		**placeholder_ptr = '$';
		(*placeholder_ptr)++;
		(*input_ptr)++;
		**placeholder_ptr = '\0';
	}
	else
	{
		var_name = find_var_name(*input_ptr + 1);
		var_value = get_env_value(env_data, var_name);
		if (var_value)
		{
			ft_strlcat(*placeholder_ptr, var_value, *placeholder_ptr
				- *placeholder_ptr + ft_strlen(var_value) + 1);
		}
		*input_ptr += ft_strlen(var_name) + 1;
		*placeholder_ptr += ft_strlen(var_value);
		free(var_name);
	}
}

static void	process_char(char **input_ptr, char **placeholder_ptr)
{
	**placeholder_ptr = **input_ptr;
	(*input_ptr)++;
	(*placeholder_ptr)++;
	**placeholder_ptr = '\0';
}

char	*replace_variables(char *input_string, t_env *env_data)
{
	char	*placeholder;
	char	*input_ptr;
	char	*placeholder_ptr;
	char	*result;

	if (!ft_strcmp(input_string, "$"))
		return (NULL);
	placeholder = create_placeholder();
	input_ptr = input_string;
	placeholder_ptr = placeholder;
	while (*input_ptr)
	{
		if (*input_ptr == '$')
		{
			process_variable(&input_ptr, &placeholder_ptr, env_data);
		}
		else
		{
			process_char(&input_ptr, &placeholder_ptr);
		}
	}
	*placeholder_ptr = '\0';
	result = ft_strdup(placeholder);
	free(placeholder);
	return (result);
}
