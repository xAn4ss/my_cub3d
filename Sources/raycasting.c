/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:20:58 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 20:26:53 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_wall_n_s(t_data *data, t_ray ray, int wallX)
{
	int		sizeH;
	t_img	NO_SO;

	if (ray.angle < M_PI && ray.angle >= 0)
		NO_SO = data->txtr.NO;
	else
		NO_SO = data->txtr.SO;
	ray.sizeH = (SCREEN_H / ray.dist) * 70;
	ray.sizeH *= 1 / cosf(ray.angle - data->sh.angle);
	if (ray.sizeH > 0)
		draw_shape_x(data, ray, wallX, NO_SO);
}

void	draw_wall_w_e(t_data *data, t_ray ray, int wallX)
{
	int 	sizeH;
	t_img	W_E;

	if(ray.angle >= 0.5 * M_PI && ray.angle < 1.5 * M_PI)
		W_E = data->txtr.WE;
	else
		W_E = data->txtr.EA;
	ray.sizeH = (SCREEN_H / ray.dist) * 70;
	ray.sizeH *= 1 / cosf(ray.angle - data->sh.angle);
	if (ray.sizeH > 0)
		draw_shape_y(data, ray, wallX, W_E);
}

double cast_coll_x(t_data *data, t_ray *ray)
{
    double	nextX;
    double	nextY;
    double	Dx;
	double	Dy;

    nextY = ray->y / 42 * 42;
    if (ray->moveY == 1)
        nextY += 42;
    nextX = ray->x + (ray->y - nextY) / tan(ray->angle);
    nextY += 2 * ray->moveY;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dy = 42;
        Dx = 42 / tan(ray->angle);
        nextX = nextX - (Dx * ray->moveY);
        nextY = nextY + (Dy * ray->moveY);
    }
    nextY -= 2 * ray->moveY;
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
	if (ray->moveX == 1)
		nextX += 42;
	nextY = ray->y + (ray->x - nextX) * tan(ray->angle);
    nextX += 2 * ray->moveX;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dx = 42;
        Dy = 42 * tan(ray->angle);
        nextX = nextX + (Dx * ray->moveX);
        nextY = nextY - (Dy * ray->moveX);
    }
    nextX -= 2 * ray->moveX;
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