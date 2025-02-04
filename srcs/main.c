#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/cub3d.h"

// -----------------------------------------------------------------------------

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
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_W) && is_player_in_wall(&eve->map->data,eve->player->plyr_x, eve->player->plyr_y - 5 * shift) == false)
		eve->player->plyr_y -= 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_S) && is_player_in_wall(&eve->map->data,eve->player->plyr_x, eve->player->plyr_y + 5 * shift) == false)
		eve->player->plyr_y += 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_A) && is_player_in_wall(&eve->map->data,eve->player->plyr_x - 5 * shift, eve->player->plyr_y) == false)
		eve->player->plyr_x -= 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_D) && is_player_in_wall(&eve->map->data,eve->player->plyr_x + 5 * shift, eve->player->plyr_y) == false)
		eve->player->plyr_x += 5 * shift;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_LEFT))
		eve->player->anglez += 0.06;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_RIGHT))
		eve->player->anglez -= 0.06;
	open_door(eve);
	// is_player_near_door(eve->map, eve->player->plyr_x, eve->player->plyr_x);
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_UP))
	// 	eve->player->angley += 0.05;
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_DOWN))
	// 	eve->player->angley -= 0.05;
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_L))
	// 	eve->player->anglex += 0.05;
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_K))
	// 	eve->player->anglex -= 0.05;
}

void game_loop(void *ev)
{
	t_eve *eve;

	eve = ev;
	mlx_delete_image(eve->mlx->mlx, eve->mlx->image);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, HEIGHT, WIDTH);
	game(eve->mlx->image, eve->player, eve->map->data);
	wall(&eve->map->data, eve->mlx->image);
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

