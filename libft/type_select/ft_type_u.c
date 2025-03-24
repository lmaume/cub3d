/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:27:56 by lmaume            #+#    #+#             */
/*   Updated: 2024/02/09 18:51:09 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

int	ft_type_u(unsigned int u, int *error)
{
	char	*str;
	int		w_len;

	str = ft_positive_itoa(u);
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
