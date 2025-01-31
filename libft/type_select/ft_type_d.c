/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:04:32 by lmaume            #+#    #+#             */
/*   Updated: 2024/02/08 18:44:31 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_type_d(int d, int *error)
{
	char	*str;
	int		w_len;

	str = ft_itoa(d);
	if (!str)
	{
		*error = CRASH_MALLOC;
		return (*error);
	}
	w_len = write(1, str, ft_strlen(str));
	if (w_len < 0)
		*error = CRASH_WRITE;
	free(str);
	return (w_len);
}
