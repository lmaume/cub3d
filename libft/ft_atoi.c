/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:30:09 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/03 18:26:59 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(char *nptr, int *error)
{
	int		i;
	int		sign;
	long	reslut;

	i = 0;
	sign = 1;
	reslut = 0;
	if (ft_strncmp(nptr, "-2147483648", ft_strlen("-2147483648")) == 0)
		return (-2147483648);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32 \
	|| nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		reslut = (reslut * 10) + (nptr[i] - '0');
		if (reslut < -2147483648 || reslut > 2147483647)
			*error = 1;
		i++;
	}
	return (sign * reslut);
}
