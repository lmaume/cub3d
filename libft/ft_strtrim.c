/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:30:55 by lmaume            #+#    #+#             */
/*   Updated: 2024/05/24 16:04:01 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	isset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*s2;

	start = 0;
	s2 = NULL;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (isset(s1[start], set))
		start++;
	if (s1[start] == '\0' || start == end)
		return (ft_calloc(1, 1));
	while (isset(s1[end], set) && end >= 1)
		end--;
	len = ((end + 1) - start) + 1;
	if (len <= 0 || start > end || end == 0)
		return (NULL);
	s2 = malloc(len);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, &s1[start], len);
	return (s2);
}
