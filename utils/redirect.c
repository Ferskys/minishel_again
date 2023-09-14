/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 03:52:44 by viferrei          #+#    #+#             */
/*   Updated: 2023/09/14 19:43:50 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	restore_original_fds(int original_fds[2])
{
	if (original_fds[0] != NO_REDIRECT)
		dup2(original_fds[0], STDIN_FILENO);
	if (original_fds[1] != NO_REDIRECT)
		dup2(original_fds[1], STDOUT_FILENO);
	return (1);
}
