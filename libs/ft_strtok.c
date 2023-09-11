/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:07:17 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/26 07:32:26 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *c)
{
	static char	*last_token = NULL;
	char		*result;

	if (str)
		last_token = str;
	if (!last_token || !*last_token)
		return (NULL);
	while (*last_token && ft_strchr(c, *last_token))
		last_token++;
	if (!*last_token)
	{
		last_token = NULL;
		return (NULL);
	}
	result = last_token;
	while (*last_token && !ft_strchr(c, *last_token))
		last_token++;
	if (*last_token)
	{
		*last_token = '\0';
		last_token++;
	}
	else
		last_token = NULL;
	return (result);
}
