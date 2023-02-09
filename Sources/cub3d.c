/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 10:34:25 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 10:46:07 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	cast_ray(t_data *data, int wallX, t_ray rayX, t_ray rayY)
{
	rayX.angle = fmod(rayX.angle, 2 * M_PI);
	if (rayX.angle < 0)
		rayX.angle += 2 * M_PI;
	rayY.angle = fmod(rayY.angle, 2 * M_PI);
	if (rayY.angle < 0)
		rayY.angle += 2 * M_PI;
	if (rayX.angle > M_PI / 2 && rayX.angle < M_PI * 3 / 2)
		rayX.moveX = -1;
	else
		rayX.moveX = 1;
	if (rayX.angle > 0 && rayX.angle < M_PI)
		rayX.moveY = -1;
	else
		rayX.moveY = 1;
	rayY.moveX = rayX.moveX;
	rayY.moveY = rayX.moveY;
	raycating(data, &rayX, &rayY, wallX);
}

void	process_game(t_data *data, t_ray ray_x, t_ray ray_y)
{
	int	wallx;

	wallx = 0;
	ray_y.x = (double)data->sh.x;
	ray_y.y = (double)data->sh.y;
	ray_x.x = (double)data->sh.x;
	ray_x.y = (double)data->sh.y;
	ray_x.angle = data->sh.angle - (M_PI / 6);
	ray_y.angle = data->sh.angle - (M_PI / 6);
	wallx = SCREEN_W;
	while (ray_x.angle < data->sh.angle + (M_PI / 6) && wallx > 0)
	{
		wallx -= 1;
		cast_ray(data, wallx, ray_x, ray_y);
		ray_x.angle += 0.055 * M_PI / 180;
		ray_y.angle += 0.055 * M_PI / 180;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	render_walls(t_data *data)
{
	t_ray	ray_x;
	t_ray	ray_y;

	data->sh.angle = fmod(data->sh.angle, (2 * M_PI));
	if (data->sh.angle < 0)
		data->sh.angle += 2 * M_PI;
	draw_background(data, get_color(data->f), get_color(data->c));
	process_game(data, ray_x, ray_y);
}

void	check_texture_files(t_data *data)
{
	if (open(data->no, O_RDONLY) == -1
		|| open(data->ea, O_RDONLY) == -1
		|| open(data->so, O_RDONLY) == -1
		|| open(data->we, O_RDONLY) == -1)
	{
		printf("Test file not found-_-\n");
		exit(EXIT_FAILURE);
	}
	init_texture(data);
	init_angle(data);
}

void	cub3d(t_data data)
{
	check_texture_files(&data);
	data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "kyub_map");
	data.img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.len, &data.img.endian);
	render_walls(&data);
	mlx_hook(data.win, 17, 1L << 2, &quit, &data);
	mlx_hook(data.win, 2, 1L << 0, pressed_key, &data);
	mlx_hook(data.win, 3, 1L << 1, release_key, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
}

// void square(t_data *data, int x, int y, void *mlx, void *win)
// {
//	  ++x;
//	  ++y;
//	  int i = x;
//	  int j = y;

//	  while (i < x + 38)
//	  {
//	  j = y;
//	  while (j < y + 38)
//	  {
//	  mlx_pixel_put(mlx, win, i, j, 0x0000FF);
//	  j++;
//	  }
//	  i++;
//	  }
// }

// void draw_map(t_data *data)
// {
//	  int x, y = 0;
//	  while (data->map && data->map[y])
//	  {
//	  x = 0;
//	  while (data->map && data->map[y][x])
//	  {
//	  if (data->map[y][x] == '1')
//	  square(data, x * 42, y * 42, data->mlx, data->win);
//	  x++;
//	  }
//	  y++;
//	  }
// }

// /*  DRAW LINE FROM PLAYER'S POSITION TO X,Y*/
// void draw_line(t_data *data, double x, double y, int moveX, int moveY, int color)
// {
//	  int dist = sqrt((((double)data->sh.x + x) * ((double)data->sh.x + x)) 
	// + ((double)data->sh.y + y) * ((double)data->sh.y + y));
//	  double Dx = data->sh.x - x;
//	  double Dy = data->sh.y - y;
//	  double Ux = Dx / dist;
//	  double Uy = Dy / dist;
//	  double pixX = data->sh.x;
//	  double pixY = data->sh.y;
//	  int i = 0;
//	  while (dist && dist < 2147483647 && dist > 0)
//	  {
//	  mlx_pixel_put(data->mlx, data->win, pixX, pixY, color);
//	  pixX -= Ux;
//	  pixY -= Uy;
//	  dist--;
//	  }
// }









