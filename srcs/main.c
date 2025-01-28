
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "../include/cub3d.h"

// -----------------------------------------------------------------------------


void	ini_player(t_player *player)
{
	player->anglex = 0;
	player->angley = 0;
	player->anglez = 0;
	player->fov = 60;
	player->plyr_x = 300;
	player->plyr_y = 300;
}

void	ini_eve(t_eve **eve)
{
	*eve = ft_calloc(sizeof(t_eve), 1);
	(*eve)->mlx = ft_calloc(sizeof(t_mlx), 1);
	(*eve)->player = ft_calloc(sizeof(t_player), 1);
	(*eve)->ray = ft_calloc(sizeof(t_ray), 1);
	(*eve)->pixels = ft_calloc(sizeof(uint8_t), WIDTH * HEIGHT * sizeof(uint32_t) + 1);
	ini_player((*eve)->player);
}

bool	my_mlx_pixel_put(mlx_image_t *image, int x, int y, unsigned int color)
{
	uint8_t* pixelstart;

	if ((y * image->width + x) * 4 > 0 && (y * image->width + x) * 4 < HEIGHT * WIDTH * 4)
	{
		pixelstart = &image->pixels[(y * image->width + x) * 4];
		// if (pixelstart++ == 0 && pixelstart++ == 0 && pixelstart++ == 0 && pixelstart == 0)
		{
			*(pixelstart++) = color >> 24;
			*(pixelstart++) = color >> 16;
			*(pixelstart++) = color >> 8;
			*(pixelstart) = color;
		}
		// else
		// 	return (true);
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

void map(char **str)
{
	str[0] = "1111111111";
	str[1] = "1000000001";
	str[2] = "1000000001";
	str[3] = "1000000001";
	str[4] = "1000110001";
	str[5] = "1000110001";
	str[6] = "1000000001";
	str[7] = "1000000001";
	str[8] = "1000000001";
	str[9] = "1111111111";
	str[10] = NULL;
}

void game_loop(void *ev)
{
	t_eve *eve;
	char **mape;

	mape = ft_calloc(sizeof(char **), 10 + 1);
	map(mape);
	eve = ev;
	mlx_delete_image(eve->mlx->mlx, eve->mlx->image);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, HEIGHT, WIDTH);
	wall(mape, eve->mlx->image);
	game(eve->mlx->image, eve->player);
	mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0);
}
// -----------------------------------------------------------------------------

int32_t main(void)
{
	t_eve	*eve;

	eve = NULL;
	ini_eve(&eve);
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
	return (EXIT_SUCCESS);
}
