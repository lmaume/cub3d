/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:27:12 by lmaume            #+#    #+#             */
/*   Updated: 2024/02/09 16:57:06 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_type_p(void *p, int *error)
{
	char	*ptr;
	int		w_len;

	if (!p)
	{
		w_len = write(1, "(nil)", 5);
		return (5);
	}
	ptr = NULL;
	ptr = ft_ptr_to_hexa((unsigned long long) p);
	if (!ptr)
	{
		*error = CRASH_MALLOC;
		return (*error);
	}
	w_len = write(1, "0x", 2);
	w_len += write(1, ptr, ft_strlen(ptr));
	if (w_len < 0)
		*error = CRASH_WRITE;
	free (ptr);
	return (w_len);
}
