/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:01:41 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 14:35:44 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokens	*iterate_to_tok_index(t_config *data)
{
	t_tokens	*temp;

	temp = data->tokens;
	while (temp && (temp->index != data->tok_index))
		temp = temp->next;
	return (temp);
}

t_reds	*create_red_list(int nodes)
{
	t_reds	*head;
	t_reds	*self;
	int		i;

	i = 0;
	if (!nodes)
		return (NULL);
	head = ft_calloc(1, sizeof(t_reds));
	self = head;
	while (i < nodes - 1)
	{
		self->next = ft_calloc(1, sizeof(t_reds));
		i++;
		self = self->next;
	}
	return (head);
}
