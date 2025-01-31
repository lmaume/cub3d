/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:04:18 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/13 17:07:21 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static
int	getsign(int number)
{
	if (number < 0)
		return (1);
	return (0);
}

static
int	getlen(int number)
{
	int	len;

	len = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		len++;
		number /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		len;

	len = getlen(n);
	sign = getsign(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = ft_calloc((len + sign) + 1, 1);
	if (!str)
		return (NULL);
	if (sign == 1)
	{
		str[0] = '-';
		n *= -1;
	}
	while (len >= sign)
	{
		if (len - (1 - sign) >= 0)
			str[len - (1 - sign)] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (str);
}
