/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:19:42 by lmaume            #+#    #+#             */
/*   Updated: 2025/03/21 16:56:36 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*ptr;
	size_t	overflow;

	if (!nmemb || !size)
		return (NULL);
	overflow = nmemb * size;
	if ((overflow / nmemb) != size)
		return (NULL);
	else
	{
		ptr = malloc((size * nmemb));
		if (!ptr)
			return (NULL);
		ft_memset(ptr, 0, size * nmemb);
	}
	return ((void *)ptr);
}
