/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:36 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/24 16:00:48 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/cub3d.h"

// -----------------------------------------------------------------------------

static void	ft_hook(void *param)
{
	t_eve	*eve;

	eve = param;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(eve->mlx->mlx);
	ft_move(eve);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_LEFT))
		eve->player->anglez -= 0.06;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_RIGHT))
		eve->player->anglez += 0.06;
	open_door(eve);
	eve->player->anglez = angle(eve->player->anglez);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_M))
	{
		if (eve->map_key_released == true)
		{
			if (eve->minimap == false)
				eve->minimap = true;
			else if (eve->minimap == true)
				eve->minimap = false;
			eve->map_key_released = false;
		}
	}
	else
		eve->map_key_released = true;
}

static void	game_loop(void *ev)
{
	t_eve	*eve;

	eve = ev;
	mlx_delete_image(eve->mlx->mlx, eve->mlx->image);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, WIDTH, HEIGHT);
	game(eve);
	eve->time.new_time++;
	mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0);
}

static void	game_start(t_eve *eve)
{
	mlx_set_cursor_mode(eve->mlx->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(eve->mlx->mlx, mouse_move, eve);
	mlx_loop_hook(eve->mlx->mlx, game_loop, eve);
	mlx_loop_hook(eve->mlx->mlx, ft_hook, eve);
	mlx_loop(eve->mlx->mlx);
}

static int	mlx_start(t_eve *eve)
{
	eve->mlx->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, HEIGHT, WIDTH);
	if (eve->mlx->mlx == NULL)
	{
		puts(mlx_strerror(mlx_errno));
		return (free_everything(eve), EXIT_FAILURE);
	}
	if (open_texture(eve) == 1)
		return (printf("One or more file not found.\n"), \
									free_everything(eve), 1);
	if (eve->mlx->image == NULL)
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return (free_everything(eve), EXIT_FAILURE);
	}
	if (mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0) == -1)
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return (free_everything(eve), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
// -----------------------------------------------------------------------------

int32_t	main(int argc, char **argv)
{
	t_eve	*eve;

	eve = NULL;
	if (is_entry_valid(argc, argv) != 0)
		return (EXIT_FAILURE);
	if (ini_eve(&eve, argc, argv) != 0)
		return (free_everything(eve), EXIT_FAILURE);
	if (mlx_start(eve) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	eve->time.old_time = mlx_get_time();
	game_start(eve);
	mlx_terminate(eve->mlx->mlx);
	free_everything(eve);
	return (printf("exit seccess\n"), EXIT_SUCCESS);
}
