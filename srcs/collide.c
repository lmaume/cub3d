#include "../include/cub3d.h"

static void	get_forward_tile(int *tile_x, int *tile_y, t_eve *eve)
{
	int	volume;

	volume = get_volume(eve->map->data.height, eve->map->data.width);
	*tile_x = (eve->player->plyr_x + \
				cos(eve->player->facing) * (volume * 0.6)) / volume;
	*tile_y = (eve->player->plyr_y - \
				sin(eve->player->facing) * (volume * 0.6)) / volume;
	printf("facing tile is %c\n", eve->map->data.map[*tile_y][*tile_x]);
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

	volume = get_volume(eve->map->data.height, eve->map->data.width);
	get_forward_tile(&tile_x, &tile_y, eve);
	if (isset(eve->map->data.map[tile_y][tile_x], "DO") == 1 \
					&& mlx_is_key_down(eve->mlx->mlx, MLX_KEY_E))
	{	
		if (eve->e_key_released == true)
		{
			toggle_door(&eve->map->data, tile_x, tile_y);
			eve->e_key_released = false;
		}
	}
	else
		eve->e_key_released = true;
}

bool	is_player_in_wall(t_data_map *data, int x, int y)
{
	int	volume;

	volume = get_volume(data->height, data->width);
	if (isset(data->map[y / volume][x / volume], "1D") == 1)
		return (true);
	return (false);
}
