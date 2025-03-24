/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:44:50 by lmaume            #+#    #+#             */
/*   Updated: 2023/12/06 16:27:34 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;

	s2 = malloc(ft_strlen(s) + 1);
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s, ft_strlen(s) + 1);
	return (s2);
}
