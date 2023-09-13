/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:55:09 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/13 20:37:18 by aqueiroz         ###   ########.fr       */
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

static

char	*replace_variables(char *input_string, t_env *env_data)
{
	char	*placeholder;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	char	*result;

	if (!ft_strcmp(input_string, "$"))
		return (NULL);
	i = 0;
	j = 0;
	placeholder = malloc(4000);
	placeholder[0] = '\0';
	while (input_string[i])
	{
		if (input_string[i] == '$')
		{
			if (!find_variable(input_string))
			{
				placeholder[j] = '$';
				j++;
				i++;
				placeholder[j] = '\0';
				continue ;
			}
			var_name = find_var_name(input_string + i + 1);
			var_value = get_env_value(env_data, var_name);
			if (var_value)
				ft_strlcat(placeholder, var_value, j + \
					ft_strlen(var_value) + 1);
			i += ft_strlen(var_name) + 1;
			j += ft_strlen(var_value);
			free(var_name);
		}
		else
		{
			placeholder[j] = input_string[i];
			i++;
			j++;
			placeholder[j] = '\0';
		}
	}
	placeholder[j] = '\0';
	result = ft_strdup(placeholder);
	free(placeholder);
	return (result);
}

void	expand_variables(t_config *data)
{
	t_tokens	*head;
	char		*expanded_value;

	head = data->tokens;
	while (data->tokens)
	{
		if (*data->tokens->value == '\'')
		{
			data->tokens = data->tokens->next;
			continue ;
		}
		expanded_value = replace_variables(data->tokens->value, data->env);
		if (expanded_value)
		{
			free(data->tokens->value);
			data->tokens->value = expanded_value;
		}
		data->tokens = data->tokens->next;
	}
	data->tokens = head;
}
