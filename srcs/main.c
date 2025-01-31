#include "../include/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "../include/cub3d.h"

// -----------------------------------------------------------------------------

void	free_map(t_map data_map)
{
	close_textures(data_map.data);
	free_tab(data_map.map_cpy);
	free_tab(data_map.data.map);
}

int	ini_map(t_map *data_map, int argc, char **argv)
{
	(void)argc;
	parse_struct(data_map, argv[1]);
	return (0);
}

void	ini_player(t_player *player, t_data_map *data)
{
	int	volume;

	volume = get_volume(data->height, data->width);
	player->anglex = 0;
	player->angley = 0;
	player->anglez = 0;
	player->fov = 60;
	player->plyr_x = (data->p_x * volume) + (volume / 2);
	player->plyr_y = (data->p_y * volume) + (volume / 2);
}

void	ini_eve(t_eve **eve, int argc, char **argv)
{
	*eve = ft_calloc(sizeof(t_eve), 1);
	(*eve)->mlx = ft_calloc(sizeof(t_mlx), 1);
	(*eve)->player = ft_calloc(sizeof(t_player), 1);
	(*eve)->ray = ft_calloc(sizeof(t_ray), 1);
	(*eve)->pixels = ft_calloc(sizeof(uint8_t), WIDTH * HEIGHT * sizeof(uint32_t) + 1);
	(*eve)->map = ft_calloc(sizeof(t_map), 1);
	ini_map((*eve)->map, argc, argv);
	ini_player((*eve)->player, &(*eve)->map->data);
	(void)argc;
	(void)argv;
}

bool	my_mlx_pixel_put(mlx_image_t *image, int x, int y, unsigned int color)
{
	uint8_t* pixelstart;

	if ((y * image->width + x) * 4 > 0 && (y * image->width + x) * 4 < HEIGHT * WIDTH * 4)
	{
		pixelstart = &image->pixels[(y * image->width + x) * 4];
		if ((uint8_t)pixelstart[0] == 0 && (uint8_t)pixelstart[1] == 0 && (uint8_t)pixelstart[2] == 0 && (uint8_t)pixelstart[3] == 0)
		{
			*(pixelstart++) = color >> 24;
			*(pixelstart++) = color >> 16;
			*(pixelstart++) = color >> 8;
			*(pixelstart) = color;
		}
		else
			return (true);
	}
	return (false);
}

void ft_hook(void* param)
{
	t_eve *eve;
	int shift;

	eve = param;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(eve->mlx->mlx);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_LEFT_SHIFT))
		shift = 2;
	else
		shift = 1;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_W))
		eve->player->plyr_y -= 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_S))
		eve->player->plyr_y += 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_A))
		eve->player->plyr_x -= 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_D))
		eve->player->plyr_x += 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_Q))
		eve->player->anglez += 0.05;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_E))
		eve->player->anglez -= 0.05;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_P))
		eve->player->angley += 0.05;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_O))
		eve->player->angley -= 0.05;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_L))
		eve->player->anglex += 0.05;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_K))
		eve->player->anglex -= 0.05;
}

void game_loop(void *ev)
{
	t_eve *eve;

	eve = ev;
	mlx_delete_image(eve->mlx->mlx, eve->mlx->image);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, HEIGHT, WIDTH);
	wall(&eve->map->data, eve->mlx->image);
	game(eve->mlx->image, eve->player, eve->map->data);
	mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0);
}
// -----------------------------------------------------------------------------

int32_t main(int argc, char **argv)
{
	t_eve	*eve;

	eve = NULL;
	if (is_entry_valid(argc, argv) != 0)
		return (printf(""), 1);
	ini_eve(&eve, argc, argv);
	if (!(eve->mlx->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(eve->mlx->image = mlx_new_image(eve->mlx->mlx, HEIGHT, WIDTH)))
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0) == -1)
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(eve->mlx->mlx, game_loop, eve);
	mlx_loop_hook(eve->mlx->mlx, ft_hook, eve);
	mlx_loop(eve->mlx->mlx);
	mlx_terminate(eve->mlx->mlx);
	// free_map((*eve)->map);
	return (EXIT_SUCCESS);
}

