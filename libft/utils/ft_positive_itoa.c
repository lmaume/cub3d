/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_positive_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:41:37 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/13 17:07:05 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libftprintf.h"

static
int	getlen(long long int number)
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

char	*ft_positive_itoa(long long int n)
{
	char	*str;
	int		len;

	len = getlen(n);
	str = ft_calloc((len + 0) + 1, 1);
	if (!str)
		return (NULL);
	while (len >= 0)
	{
		if (len - (1) >= 0)
			str[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (str);
}
