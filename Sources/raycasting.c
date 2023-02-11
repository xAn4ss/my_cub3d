/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:20:58 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 22:46:10 by ybachaki         ###   ########.fr       */
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
	t_img	W;

	if(ray.angle >= 0.5 * M_PI && ray.angle < 1.5 * M_PI)
		W = data->txtr.WE;
	else
		W = data->txtr.EA;
	ray.size_h = (SCREEN_H / ray.dist) * 70;
	ray.size_h *= 1 / cosf(ray.angle - data->sh.angle);
	if (ray.size_h > 0)
		draw_shape_y(data, ray, wallX, W);
}

double cast_coll_x(t_data *data, t_ray *ray)
{
    double	nextX;
    double	nextY;
    double	Dx;
	double	Dy;

    nextY = ray->y / 42 * 42;
    if (ray->mov_y == 1)
        nextY += 42;
    nextX = ray->x + (ray->y - nextY) / tan(ray->angle);
    nextY += 2 * ray->mov_y;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dy = 42;
        Dx = 42 / tan(ray->angle);
        nextX = nextX - (Dx * ray->mov_y);
        nextY = nextY + (Dy * ray->mov_y);
    }
    nextY -= 2 * ray->mov_y;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX) * ((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY) * ((double)data->sh.y - nextY)));
}

double cast_coll_y(t_data *data, t_ray *ray)
{
	double	nextX;
	double	nextY;
	double	Dx;
	double	Dy;

	nextX = ray->x / 42 * 42;
	if (ray->mov_x == 1)
		nextX += 42;
	nextY = ray->y + (ray->x - nextX) * tan(ray->angle);
    nextX += 2 * ray->mov_x;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dx = 42;
        Dy = 42 * tan(ray->angle);
        nextX = nextX + (Dx * ray->mov_x);
        nextY = nextY - (Dy * ray->mov_x);
    }
    nextX -= 2 * ray->mov_x;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX) * ((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY) * ((double)data->sh.y - nextY)));
}

void raycating (t_data *data, t_ray *rayX, t_ray *rayY, int wallX)
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