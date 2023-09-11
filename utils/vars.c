/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:09:23 by fsuomins          #+#    #+#             */
/*   Updated: 2023/09/10 14:34:38 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_variable(char	*str)
{
	while (*str)
	{
		if (*str == '$' && is_variable(str[1]))
			return (str++);
		str++;
	}
	return (NULL);
}

int	is_variable(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

void	*free_pp_char(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		pp[i] = safe_free (pp[i]);
		i++;
	}
	pp = safe_free(pp);
	return (NULL);
}

char	*get_var_name(char	*var_head)
{
	size_t	len;

	len = 0;
	if (*var_head == '$')
		var_head++;
	while (var_head[len] && is_variable(var_head[len]))
		len++;
	return (ft_substr(var_head, 0, len));
}
