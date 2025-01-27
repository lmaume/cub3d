/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:25:35 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/27 18:08:41 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	angle_x(t_player *player, int x, int y, int z)
{
	return ((cos(player->angley)
			* ((sin(player->anglez) * y) + (cos(player->anglez)
					* x))) - (sin(player->angley) * z));
}

int	angle_y(t_player *player, int x, int y, int z)
{
	return ((sin(player->anglex)
			* ((cos(player->angley) * z) + (sin(player->angley)
					* ((sin(player->angley) * y) + (cos(player->anglez)
							* x))))) + (cos(player->anglex)
			* ((cos(player->anglez) * y)
				- (sin(player->anglez) * x))));
}

int angle_z(t_player *player, int x, int y, int z)
{
	return ((cos(player->anglex)
			* ((cos(player->angley) * z) + (sin(player->angley)
					* ((sin(player->angley) * y) + (cos(player->anglez)
							* x))))) - (sin(player->anglex)
			* ((cos(player->anglez) * x))));
}