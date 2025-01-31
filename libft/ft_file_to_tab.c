/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:15:21 by lmaume            #+#    #+#             */
/*   Updated: 2025/01/30 14:34:02 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line/get_next_line.h"

static int	count_file_size(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}

char	**ft_file_to_tab(char *filename)
{
	char	**tab;
	int		fd;
	int		i;

	i = 0;
	tab = ft_calloc(sizeof(char *), count_file_size(filename) + 1);
	if (tab == NULL)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(tab);
		return (NULL);
	}
	tab[i] = get_next_line(fd);
	while (tab[i] != NULL)
	{
		i++;
		tab[i] = get_next_line(fd);
	}
	close(fd);
	return (tab);
}
