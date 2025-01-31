/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_porcent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:27:21 by lmaume            #+#    #+#             */
/*   Updated: 2024/02/12 15:15:04 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_type_porcent(char c, int *error)
{
	int		i;

	i = 1;
	if (c != '%')
	{
		if (write(1, "%", 1) < 0)
			*error = CRASH_WRITE;
		i++;
	}
	if (write(1, &c, 1) < 0)
		*error = CRASH_WRITE;
	return (i);
}
