/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:08 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/24 15:48:21 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_move(void *param)
{
	static int	old_x = INT8_MIN;
	int			x;
	int			y;
	double		new_angle;
	t_eve		*eve;

	eve = param;
	mlx_get_mouse_pos(eve->mlx->mlx, &x, &y);
	new_angle = ((double)(x - old_x) / WIDTH) * (2 * PI) / 10;
	if (old_x == INT8_MIN)
	{
		old_x = x;
		return ;
	}
	old_x = x;
	eve->player->anglez += (new_angle);
}

static void	get_forward_tile(int *tile_x, int *tile_y, t_eve *eve)
{
	int	volume;

	volume = eve->map->data.volume;
	*tile_x = (eve->player->plyr_x + \
				cos(eve->player->anglez) * (volume * 0.6)) / volume;
	*tile_y = (eve->player->plyr_y + \
				sin(eve->player->anglez) * (volume * 0.6)) / volume;
}

static void	toggle_door(t_data_map *data, int x, int y)
{
	if (data->map[y][x] == 'D')
		data->map[y][x] = 'O';
	else if (data->map[y][x] == 'O')
		data->map[y][x] = 'D';
}

void	open_door(t_eve *eve)
{
	int	volume;
	int	tile_x;
	int	tile_y;

	volume = eve->map->data.volume;
	get_forward_tile(&tile_x, &tile_y, eve);
	if (isset(eve->map->data.map[tile_y][tile_x], "DO") == 1 \
					&& mlx_is_key_down(eve->mlx->mlx, MLX_KEY_E))
	{
		if (eve->e_key_released == true)
		{
			if ((int)eve->player->plyr_x / volume != \
			tile_x || (int)eve->player->plyr_y / volume != tile_y)
			{
				toggle_door(&eve->map->data, tile_x, tile_y);
				eve->e_key_released = false;
			}
		}
	}
	else
		eve->e_key_released = true;
}

bool	is_player_in_wall(t_data_map *data, int x, int y)
{
	int	volume;

	volume = data->volume;
	if (isset(data->map[y / volume][x / volume], "1D") == 1)
		return (true);
	return (false);
}
