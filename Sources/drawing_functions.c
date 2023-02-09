/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:24:23 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 19:49:36 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_color(char *s)
{
	char	**clrs;
	int		color;
	int		i;
	int		p;

	p = 2;
	i = 0;
	color = 0;
	clrs = ft_split(s, ',');
	while (i < 3)
	{
		color += ft_atoi(clrs[i]) * pow(256, p);
		p--;
		i++;
	}
	return (color);
}

void	draw_background(t_data *data, int floorColor, int ceilColor)
{
	char	*pixel;
	int		x;
	int		y;

	y = -1;
	while (++y < SCREEN_H / 2)
	{
		x = -1;
		while (++x < SCREEN_W)
			*(int *)(data->img.addr + (y * data->img.len + x * 4)) = ceilColor;
	}
	y = SCREEN_H / 2 - 1;
	while (++y < SCREEN_H)
	{
		x = -1;
		while (++x < SCREEN_W)
			*(int *)(data->img.addr + (y * data->img.len + x * 4)) = floorColor;
	}
}

void	draw_shape_x(t_data *data, t_ray ray, int x, t_img wall)
{
	char	*pixel;
	int		i;
	int		j;
	int		py;

	i = 0;
	py = 0;
	wall.addr = mlx_get_data_addr(wall.img, &wall.bpp, &wall.len, &wall.endian);
	while (i < 1)
	{
		j = 0;
		py = (SCREEN_H / 2) - (ray.sizeH / 2);
		while (j < ray.sizeH)
		{
			if (py >= 0 && py < SCREEN_H)
			{
				ft_memcpy(data->img.addr + py * data->img.len + x * 4, wall.addr
					+ (j * 42 / ray.sizeH * wall.len + ray.x % 42 * 4), 3);
			}
			py++;
			j++;
		}
		x++;
		i++;
	}
}

void	draw_shape_y(t_data *data, t_ray ray, int x, t_img wall)
{
	char	*pixel;
	int		i;
	int		j;
	int		py;

	i = 0;
	py = 0;
	wall.addr = mlx_get_data_addr(wall.img, &wall.bpp, &wall.len, &wall.endian);
	while (i < 1)
	{
		j = 0;
		py = (SCREEN_H / 2) - (ray.sizeH / 2);
		while (j < ray.sizeH)
		{
			if (py >= 0 && py < SCREEN_H)
			{
				ft_memcpy(data->img.addr + py * data->img.len + x * 4, wall.addr
					+ j * 42 / ray.sizeH * wall.len + ray.y % 42 * 4, 3);
			}
			py++;
			j++;
		}
		x++;
		i++;
	}
}

void	ft_error(t_data *data)
{
	printf("somethin's wrong with text_file -_-\n");
	exit(EXIT_FAILURE);
}

int	quit(int keycode, t_data *data)
{
        // should free;
	exit(0);
}
