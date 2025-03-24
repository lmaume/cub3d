/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:20:20 by lmaume            #+#    #+#             */
/*   Updated: 2025/01/28 15:06:15 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tabchr(char **tab, int c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (tab[i] != NULL)
	{
		tmp = ft_strchr(tab[i], c);
		if (tmp != NULL)
			return (tmp);
		i++;
	}
	return (NULL);
}

char	*ft_tabcmp(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		if (ft_strncmp(tab[i], str, ft_strlen(str)) == 0)
			return (tab[i]);
		i++;
	}
	return (NULL);
}

int	isset_tab(char *str, char **set)
{
	int	i;

	i = 0;
	while (set[i] != NULL)
	{
		if (ft_strncmp(str, set[i], ft_linelen(set[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}
