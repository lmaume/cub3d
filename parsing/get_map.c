/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:52:55 by mlapique          #+#    #+#             */
/*   Updated: 2025/04/08 15:45:01 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	get_map_line(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		while (ft_iswhite_space(tab[i][j]) == 1)
			j++;
		if (isset(tab[i][j], "10DO") == 1)
			return (i);
		j = 0;
		i++;
	}
	return (0);
}

static int	get_map_width(char **map, int start)
{
	int	i;
	int	j;
	int	w_max;

	i = start;
	j = 0;
	w_max = 0;
	while (map[i] != NULL && (map[i][0] != '\0'))
	{
		while (map[i][j] != '\0')
			j++;
		if (j > w_max)
			w_max = j;
		j = 0;
		i++;
	}
	return (w_max - 1);
}

int	get_map_size(t_map *data_map, char **map, int start)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (map[i] != NULL && (map[i][0] != '\0'))
	{
		while (isset(map[i][j], "10NSEWDO") == 0 && map[i][j] != '\0')
			j++;
		j = 0;
		i++;
	}
	data_map->data.height = ((i - start) - 1);
	data_map->data.width = get_map_width(map, start);
	return (i);
}

int	map_alloc(t_map *data_map, char **tab)
{
	int	i;
	int	j;
	int	len;
	int	size;

	len = 0;
	j = 0;
	i = get_map_line(tab) - 1;
	size = get_map_size(data_map, tab, i);
	data_map->data.map = ft_calloc(sizeof(char *), size - (i - 1));
	data_map->map_cpy = ft_calloc(sizeof(char *), size - (i - 1));
	if (data_map->data.map == NULL || data_map->map_cpy == NULL)
		return (1);
	while (++i < size)
	{
		len = ft_strlen(tab[i]);
		data_map->data.map[j] = ft_calloc(sizeof(char), len);
		data_map->map_cpy[j] = ft_calloc(sizeof(char), len);
		if (data_map->data.map[j] == NULL || data_map->map_cpy[j] == NULL)
			return (1);
		ft_memcpy(data_map->data.map[j], tab[i], len);
		ft_memcpy(data_map->map_cpy[j], tab[i], len);
		j++;
	}
	return (0);
}
