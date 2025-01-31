/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:33:48 by lmaume            #+#    #+#             */
/*   Updated: 2024/11/05 16:48:39 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

static
int	ft_intlen(unsigned int number)
{
	int	len;

	len = 0;
	while (number >= 1)
	{
		number /= 16;
		len++;
	}
	return (len);
}

char	*ft_hexa_converter(unsigned int *base_number)
{
	int		i;
	char	*hextable;
	char	*result;

	result = ft_calloc(ft_intlen(*base_number) + 1, 1);
	if (!result)
		return (NULL);
	hextable = "0123456789abcdef";
	i = ft_intlen(*base_number);
	while (i-- != 0)
	{
		result[i] = hextable[*base_number % 16];
		*base_number /= 16;
	}
	return (result);
}
