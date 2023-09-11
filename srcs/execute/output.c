/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 02:58:01 by coder             #+#    #+#             */
/*   Updated: 2023/09/10 14:31:43 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	tok_count_outputs(t_tokens *arg_temp)
{
	t_tokens	*temp;
	int			ret;

	ret = 0;
	temp = arg_temp;
	if (temp && temp->type == OPTOKEN)
		temp = temp->next;
	while (temp && temp->type != OPTOKEN)
	{
		if (temp->type == REDTOKEN)
		{
			if (!ft_strcmp(">", temp->value))
				ret++;
			else if (!ft_strcmp(">>", temp->value))
				ret++;
		}
		temp = temp->next;
	}
	return (ret);
}

static void	tok_fill_outlist(t_reds *self, t_tokens *tokens)
{
	if (tokens && tokens->type == OPTOKEN)
		tokens = tokens->next;
	while (tokens && self && tokens->type != OPTOKEN)
	{
		if (tokens->type == REDTOKEN)
		{
			if (!ft_strcmp(">", tokens->value))
			{
				self->type = OVERWRITE;
				self->target = ft_strdup(tokens->next->value);
				self = self->next;
			}
			if (!ft_strcmp(">>", tokens->value))
			{
				self->type = APPEND;
				self->target = ft_strdup(tokens->next->value);
				self = self->next;
			}
		}
		tokens = tokens->next;
	}
}

/*
** If it goes in, it goes out.
*/
t_reds	*tok_output(t_config *data)
{
	t_tokens	*temp;
	t_reds		*self;
	int			count;

	temp = iterate_to_tok_index(data);
	count = tok_count_outputs(temp);
	self = create_red_list(count);
	if (self)
		tok_fill_outlist(self, temp);
	return (self);
}
