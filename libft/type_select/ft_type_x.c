/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:28:02 by lmaume            #+#    #+#             */
/*   Updated: 2024/02/09 14:10:16 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_type_x(unsigned int x, int *error)
{
	char	*ptr;
	int		w_len;

	if (!x)
	{
		w_len = write(1, "0", 1);
		return (1);
	}
	ptr = ft_hexa_converter(&x);
	if (!ptr)
	{
		*error = CRASH_MALLOC;
		return (*error);
	}
	w_len = write(1, ptr, ft_strlen(ptr));
	if (w_len < 0)
		*error = CRASH_WRITE;
	free (ptr);
	return (w_len);
}
