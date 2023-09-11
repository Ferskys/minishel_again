/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 01:59:31 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 19:39:33 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	tok_count_args(t_tokens *temp)
{
	t_tokens	*other;
	int			ret;

	other = temp;
	ret = 0;
	if (other && (other->type == COMTOKEN || other->type == BITOKEN))
	{
		ret++;
		other = other->next;
	}
	while (other && other->type == WORDTOKEN)
	{
		ret++;
		other = other->next;
	}
	return (ret);
}

char	**tok_args(t_config *data)
{
	t_tokens	*temp;
	char		**ret;
	int			count;
	int			i;

	count = 0;
	i = 0;
	temp = iterate_to_tok_index(data);
	while (temp && (temp->type != COMTOKEN && temp->type != BITOKEN))
	{
		temp = temp->next;
		if (temp && temp->type == OPTOKEN)
			return (NULL);
	}
	if (!temp)
		return (NULL);
	count = tok_count_args(temp);
	ret = ft_calloc(count + 1, sizeof(char *));
	while (i < count)
	{
		ret[i] = ft_strdup(temp->value);
		temp = temp->next;
		i++;
	}
	return (ret);
}
