/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:35:09 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/26 07:32:12 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str, char *str2)
{
	while (*str && *str2)
	{
		if (*str != *str2)
			break ;
		str++;
		str2++;
	}
	return (*str - *str2);
}
