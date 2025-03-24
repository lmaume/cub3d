/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:17:18 by lmaume            #+#    #+#             */
/*   Updated: 2023/12/06 16:26:47 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	str = (const unsigned char *)s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (str[i] != (unsigned char)c && i < n - 1)
	{
		i++;
	}
	if ((int)str[i] == (unsigned char)c)
		return ((void *)(str + i));
	else
		return (NULL);
}
