/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:41:51 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/27 18:41:08 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_wall(char **str, int i, int j)
{
    t_point *p1;
    t_point *p2;
    
    if ()
}

int wall(char **str)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (str[i])
    {
        while (str[i][j])
        {
            if (str[i][j] == '1')
                draw_wall(str, i, j);
            j++;
        }
        i++;
    }
    
}