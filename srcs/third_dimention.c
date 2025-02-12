#include "../include/cub3d.h"

// void	draw_wall_height(t_eve *eve, mlx_image_t *image, int x, double distance)
// {
// 	double				wall_height;
// 	int					y_start;
// 	int					y_end;
// 	int					y;
// 	int					x_temp;
// 	int					line_width;
// 	t_line_necessary	draw_line;
// 	uint32_t			color;

// 	(void)eve;
// 	(void)draw_line;
// 	wall_height = (HEIGHT * 30) / distance;
// 	y_start = (HEIGHT / 2) - (wall_height / 2);
// 	y_end = (HEIGHT / 2) + (wall_height / 2);
// 	y = y_start;
// 	color = 0xDD88DDFF;
// 	while (y < y_end)
// 	{
// 		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 		{
// 			line_width = 50;
// 			x_temp = x;
// 			while (line_width > 0)
// 			{
// 				if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_0))
// 					color *= 1.2;
// 				mlx_put_pixel(image, x_temp, y, color);
// 				x_temp++;
// 				line_width--;
// 			}
// 		}
// 		y++;
// 	}
// }

void draw_wall_height(t_eve *eve, mlx_image_t *image, int x, double distance)
{
	double wall_height;
	int y_start, y_end, y;
	int line_width;  // Dessine chaque pixel par rayon de manière fine
	int x_temp;

	(void)eve;
	wall_height = (HEIGHT * 30) / distance;
	y_start = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	y = y_start;
	while (y < y_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			line_width = 11;
			x_temp = x;
			while (line_width > 0)
			{
				mlx_put_pixel(image, x_temp, y, 0x00DDDDFF);
				x_temp++;
				line_width--;
			}
		}
		y++;
    }
}
