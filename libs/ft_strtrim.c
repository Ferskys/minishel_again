/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:43:39 by fsuomins          #+#    #+#             */
/*   Updated: 2023/07/21 21:17:10 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	s1_len;
	size_t	start_index;
	size_t	end_index;
	size_t	trimmed_len;
	char	*trimmed_str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	start_index = 0;
	end_index = s1_len - 1;
	while (s1[start_index] && ft_strchr(set, s1[start_index]) != NULL)
		start_index++;
	while (s1[end_index] && end_index > start_index && \
	ft_strchr(set, s1[end_index]) != NULL)
		end_index--;
	trimmed_len = end_index - start_index + 1;
	trimmed_str = (char *)malloc((trimmed_len + 1) * sizeof(char));
	if (trimmed_str == NULL)
		return (NULL);
	ft_memcpy(trimmed_str, s1 + start_index, trimmed_len);
	trimmed_str[trimmed_len] = '\0';
	return (trimmed_str);
}
