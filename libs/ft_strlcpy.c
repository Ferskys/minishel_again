/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:05:29 by fsuomins          #+#    #+#             */
/*   Updated: 2023/07/21 21:17:08 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen)
{
	size_t	src_size;

	src_size = ft_strlen(src);
	if (maxlen > 0)
	{
		if (src_size >= maxlen)
		{
			ft_memcpy(dst, src, maxlen);
			dst[maxlen - 1] = '\0';
		}
		else
		{
			ft_memcpy(dst, src, src_size);
			dst[src_size] = '\0';
		}
	}
	return (src_size);
}
