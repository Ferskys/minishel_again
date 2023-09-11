/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:42:50 by fsuomins          #+#    #+#             */
/*   Updated: 2023/07/21 21:17:04 by aqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	val;

	p = ptr;
	val = (unsigned char)value;
	while (num-- > 0)
		*p++ = val;
	return (ptr);
}

/*Description

The C library function void *memset(void *str, int c, size_t n) copies the 
character c (an unsigned char) to the first n characters of the string
pointed to, by the argument str.
 
Declaration

Following is the declaration for memset() function.

void *memset(void *str, int c, size_t n)

Parameters

    str − This is a pointer to the block of memory to fill.

    c − This is the value to be set. The value is passed as an int,
    but the function fills the block of memory using the unsigned char
    conversion of this value.

    n − This is the number of bytes to be set to the value.

Return Value

This function returns a pointer to the memory area str.*/