/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:00:00 by lmaume            #+#    #+#             */
/*   Updated: 2025/01/27 14:24:49 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	ft_bzero(void *s, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		((unsigned char *)s)[i] = '\0';
// 		i++;
// 	}
// }

void	*ft_memmcpy(void *dest, void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (n == 1)
		ft_bzero(dest, BUFFER_SIZE - 1);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strldup(char *s, size_t len)
{
	char	*s2;

	s2 = malloc(len + 2);
	if (s2 == NULL)
		return (NULL);
	ft_memmcpy(s2, s, len + 2);
	s2[len + 1] = '\0';
	return (s2);
}

static
char	*protec_join(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (ft_strldup(s1, ft_strlen(s1)));
	return (ft_strldup(s2, ft_strlen(s2)));
}

char	*ft_strljoin(char *s1, char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ret;

	if (!s1 || !s2)
		return (protec_join(s1, s2));
	i = 0;
	j = 0;
	ret = malloc(ft_strlen(s1) + len + 2);
	if (!ret)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && j <= len)
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	free(s1);
	return (ret);
}
