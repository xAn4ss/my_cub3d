/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:20:58 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 17:35:36 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_wall_n_s(t_data *data, t_ray ray, int wallX)
{
	t_img	no_so;

	if (ray.angle < M_PI && ray.angle >= 0)
		no_so = data->txtr.NO;
	else
		no_so = data->txtr.SO;
	ray.size_h = (SCREEN_H / ray.dist) * 70;
	ray.size_h *= 1 / cosf(ray.angle - data->sh.angle);
	if (ray.size_h > 0)
		draw_shape_x(data, ray, wallX, no_so);
}

void	draw_wall_w_e(t_data *data, t_ray ray, int wallX)
{
	t_img	we_ea;

	if (ray.angle >= 0.5 * M_PI && ray.angle < 1.5 * M_PI)
		we_ea = data->txtr.WE;
	else
		we_ea = data->txtr.EA;
	ray.size_h = (SCREEN_H / ray.dist) * 70;
	ray.size_h *= 1 / cosf(ray.angle - data->sh.angle);
	if (ray.size_h > 0)
		draw_shape_y(data, ray, wallX, we_ea);
}

double	cast_coll_x(t_data *data, t_ray *ray)
{
	double	next_x;
	double	next_y;
	double	dx;
	double	dy;

	next_y = ray->y / 42 * 42;
	if (ray->mov_y == 1)
		next_y += 42;
	next_x = ray->x + (ray->y - next_y) / tan(ray->angle);
	next_y += 2 * ray->mov_y;
	while (next_x < 42 * data->x_len && next_x > 0
		&& next_y < 42 * data->y_len && next_y > 0
		&& data->map[(int)floor(next_y / 42)]
		[(int)floor(next_x / 42)] != '1')
	{
		dy = 42;
		dx = 42 / tan(ray->angle);
		next_x = next_x - (dx * ray->mov_y);
		next_y = next_y + (dy * ray->mov_y);
	}
	next_y -= 2 * ray->mov_y;
	ray->x = (int)next_x;
	ray->y = (int)next_y;
	return (sqrt(((data->sh.x - next_x) * (data->sh.x - next_x))
			+ (data->sh.y - next_y) * (data->sh.y - next_y)));
}

double	cast_coll_y(t_data *data, t_ray *ray)
{
	double	next_x;
	double	next_y;
	double	dx;
	double	dy;

	next_x = ray->x / 42 * 42;
	if (ray->mov_x == 1)
		next_x += 42;
	next_y = ray->y + (ray->x - next_x) * tan(ray->angle);
	next_x += 2 * ray->mov_x;
	while (next_x < 42 * data->x_len && next_x > 0
		&& next_y < 42 * data->y_len && next_y > 0
		&& data->map[(int)floor(next_y / 42)]
		[(int)floor(next_x / 42)] != '1')
	{
		dx = 42;
		dy = 42 * tan(ray->angle);
		next_x = next_x + (dx * ray->mov_x);
		next_y = next_y - (dy * ray->mov_x);
	}
	next_x -= 2 * ray->mov_x;
	ray->x = (int)next_x;
	ray->y = (int)next_y;
	return (sqrt(((data->sh.x - next_x) * (data->sh.x - next_x))
			+ (data->sh.y - next_y) * (data->sh.y - next_y)));
}

void	raycating(t_data *data, t_ray *rayX, t_ray *rayY, int wallX)
{
	rayX->dist = cast_coll_x(data, rayX);
	rayY->dist = cast_coll_y(data, rayY);
	if (rayX->x <= 0)
		rayX->dist = 2147483647;
	if (rayY->y <= 0)
		rayY->dist = 2147483647;
	if (rayX->dist < rayY->dist)
		draw_wall_n_s(data, *rayX, wallX);
	else if (rayX->dist > rayY->dist)
		draw_wall_w_e(data, *rayY, wallX);
}
