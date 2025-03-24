/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:49 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/22 19:28:25 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "limits.h"

int	wall_hit(double x, double y, t_eve *eve)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / VOLUME);
	y_m = floor (y / VOLUME);
	if ((y_m >= eve->map->data.height || \
		x_m >= eve->map->data.width) || y_m < 0 || x_m < 0)
		return (0);
	if (eve->map->data.map[y_m] && x_m <= \
		(int)ft_strlen(eve->map->data.map[y_m]))
		if (isset(eve->map->data.map[y_m][x_m], "1D") == 1)
			return (0);
	return (1);
}

int	inter_check(double angle, double *inter, double *step, bool is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += VOLUME;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*inter += VOLUME;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

double	get_y_crossing(t_eve *eve, double angle, int ray_nb)
{
	double	cx;
	double	cy;
	double	x_step;
	double	y_step;
	int		modif;

	x_step = VOLUME;
	y_step = VOLUME * tan(angle);
	cx = floor(eve->player->plyr_x / VOLUME) * VOLUME;
	modif = inter_check(angle, &cx, &x_step, false);
	cy = eve->player->plyr_y + (cx - eve->player->plyr_x) * tan(angle);
	if ((unit_circle(angle, true) && y_step < 0) || \
	(!unit_circle(angle, true) && y_step > 0))
		y_step *= -1;
	while (wall_hit(cx - modif, cy, eve))
	{
		cx += x_step;
		cy += y_step;
	}
	if (eve->walls->mo_zaik == true)
		eve->walls->y_touch[ray_nb] = (int)cy;
	else
		eve->walls->y_touch[ray_nb] = cy;
	return (sqrt(pow(cx - eve->player->plyr_x, 2) \
	+ pow(cy - eve->player->plyr_y, 2)));
}

double	get_x_crossing(t_eve *eve, double angle, int ray_nb)
{
	double	cx;
	double	cy;
	double	x_step;
	double	y_step;
	int		modif;

	y_step = VOLUME;
	x_step = VOLUME / tan(angle);
	cy = floor(eve->player->plyr_y / VOLUME) * VOLUME;
	modif = inter_check(angle, &cy, &y_step, true);
	cx = eve->player->plyr_x + (cy - eve->player->plyr_y) / tan(angle);
	if ((unit_circle(angle, 0) && x_step > 0) \
	|| (!unit_circle(angle, 0) && x_step < 0))
		x_step *= -1;
	while (wall_hit(cx, cy - modif, eve))
	{
		cx += x_step;
		cy += y_step;
	}
	if (eve->walls->mo_zaik == true)
		eve->walls->x_touch[ray_nb] = (int)cx;
	else
		eve->walls->x_touch[ray_nb] = cx;
	return (sqrt(pow(cx - eve->player->plyr_x, 2) + \
	pow(cy - eve->player->plyr_y, 2)));
}

void	raycasting(t_eve *eve, t_wall *walls)
{
	int					ray_nb;
	double				x_crossing;
	double				y_crossing;
	double				offset;
	double				div;

	ray_nb = -1;
	div = (eve->player->fov / WIDTH);
	offset = eve->player->anglez - (eve->player->fov / 2);
	while (++ray_nb < WIDTH)
	{
		walls->north_south[ray_nb] = false;
		x_crossing = get_x_crossing(eve, angle(offset), ray_nb);
		y_crossing = get_y_crossing(eve, angle(offset), ray_nb);
		if (x_crossing <= y_crossing)
			eve->walls->distance[ray_nb] = x_crossing;
		else
		{
			eve->walls->distance[ray_nb] = y_crossing;
			walls->north_south[ray_nb] = true;
		}
		walls->distance[ray_nb] *= cos(angle(offset - eve->player->anglez));
		walls->angle[ray_nb] = angle(offset);
		offset += div;
	}
}
