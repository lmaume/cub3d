/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:42:33 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/05 15:43:40 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include "libft.h"

void	free_tab(char **tab)
{
	char	**tab_start;

	tab_start = tab;
	if (tab == NULL)
		return ;
	while (*tab != NULL)
	{
		free(*tab);
		tab++;
	}
	free(tab_start);
}

static
int	wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static
char	**fill_tab(char const *s, char c, char **tab, char **tab_start)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		if (i == j)
			break ;
		*tab = ft_substr(s, i, (j - i));
		if (!*tab)
		{
			free_tab(tab_start);
			return (NULL);
		}
		tab++;
		i = j;
	}
	*tab = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(wordcount(s, c) + 1, sizeof(char *));
	if (!tab)
	{
		free_tab(tab);
		return (NULL);
	}
	if (fill_tab(s, c, tab, tab) == NULL)
		return (NULL);
	return (tab);
}
