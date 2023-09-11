/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 12:23:37 by fsuomins          #+#    #+#             */
/*   Updated: 2023/07/21 21:17:10 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	sub_len;
	char	*substr;

	s_len = ft_strlen(s);
	if (start >= s_len || !s)
		return (NULL);
	sub_len = len;
	if (start + sub_len > s_len)
		sub_len = s_len - start;
	substr = ft_calloc(sub_len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_memcpy(substr, s + start, sub_len);
	return (substr);
}
