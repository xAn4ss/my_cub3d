/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:26:38 by ybachaki          #+#    #+#             */
/*   Updated: 2023/01/30 11:33:49 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	wall(int y, int x, int lines, char *ptr)
{
	int	i;
	int	j;

	i = 0;
	while(i < 32)
	{
		j = 0;
		while (j < 32)
		{
			*(int*)(ptr + ((x + j) * 4) + ((y + i) * lines)) = 16777215;
			j++;
		}
		i++;
	}
}

void	free_s(int y, int x, int lines , char *ptr)
{
	int	i;
	int	j;

	i = 0;
	while(i < 32)
	{
		j = 0;
		while (j < 32)
		{
			*(int*)(ptr + ((x + j) * 4) + ((y + i) * lines)) = 23967;
			j++;
		}
		i++;
	}
}

void	player(int y, int x, int lines, char *ptr, t_data *data)
{
	int	i;
	int	j;
	double angle;
	int	rays;

	i = 0;
	rays = data->y_len * 32;
	while(i < 7)
	{
		j = 0;
		while (j < 8)
		{
			*(int*)(ptr + ((x - 3 + j) * 4) + ((y - 3 + i) * lines)) = 16711680;
			j++;
		}
		i++;
	}
	i = 0;
	angle = data->player.angle - (30 * (M_PI/180));
	while(i < rays)
	{
		ray(data, angle);
		i++;
		angle += 60 * (M_PI/180) / (rays);

	}
}

void	init_img(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == '1')
				wall(i * 32, j * 32, data->mlx.l_size, data->mlx.ptr);
			else if (data->map[i][j] == '0')
				free_s(i * 32, j * 32, data->mlx.l_size, data->mlx.ptr);
			else if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				free_s(i * 32, j * 32, data->mlx.l_size, data->mlx.ptr);
			}
			j++;
		}
		i++;
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 119)
	{	
		data->player.move_u_d = 1;
	}
	else if (keycode == 115)
	{
		data->player.move_u_d = -1;
	}
	else if (keycode == 2)
		data->player.position_x += round(cos(data->player.angle) * 5);

	else if (keycode == 65363)
		data->player.moove_r_l = 1;
	else if (keycode == 65361)
		data->player.moove_r_l = -1;
	printf("%d\n", keycode);
	// init_img(data);
	// printf("x = %d, y = %d\n", data->player.position_x, data->player.position_y);
	// player(data->player.position_y, data->player.position_x, data->mlx.l_size, data->mlx.ptr, data);
	// mlx_clear_window(data->mlx.mlx, data->mlx.win);
	// mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0,0);
	return 0;
}
/// to be continuue.....
int	key_release(int keycode, t_data *data)
{

	if (keycode == 119)
	{	
		data->player.move_u_d = 0;
	}
	else if (keycode == 115)
	{
		data->player.move_u_d = 0;
	}
	else if (keycode == 65363)
		data->player.moove_r_l = 0;
	else if (keycode == 65361)
		data->player.moove_r_l = 0;
	return 0;
}

void	dda(t_data *data, double x, double y)
{
	int		dx;
	int		dy;
	int		steps;
	double	x_inc;
	double	y_inc;
	double	x1;
	double	y1;
	int		i;

	if (x > data->x_len * 32 || y > data->y_len *32 || x < 0 || y < 0)
		return ;

	dx = x - data->player.position_x;
	dy = y - data->player.position_y;

	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	x_inc = (float)dx / steps;
	y_inc = (float)dy / steps;

	i = 0;

	x1 = data->player.position_x;
	y1 = data->player.position_y;
	while (i < steps)
	{
		*(int*)(data->mlx.ptr + (((int)(x1 + 0.5) * 4) + ((int)(y1 + 0.5) * data->mlx.l_size))) = 16711680;
		x1 += x_inc;
		y1 += y_inc;
		i++;
	}
}
///////

int	wall_hit(t_data *data, double x, double y)
{
	int i;
	int j;

	i = y / 32;
	j = x / 32;
	if (i > ft_len(data->map) || i < 0 || j < 0 || j > ft_strlen(data->map[i]))
		return -1;
	if (data->map[i][j] == '1')
		return 1;
	return 0;
}

int	distance(int x1, int y1, int x2, int y2)
{
	int res;

	res = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return res;
}

void	ray(t_data *data, double ray_angle)
{
	double x_inter, y_inter, x_steps, y_steps, v_dist, h_dist;
	int h_found, i = 0;
	
	ray_angle = fmod(ray_angle , (2 * M_PI));
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;

	y_inter = 32 * floor(data->player.position_y  / 32);
	if (ray_angle < M_PI && ray_angle > 0)
		y_inter += 32;

	x_inter = data->player.position_x + (y_inter - data->player.position_y) / tan(ray_angle);
	
	y_steps = 32;
	if (ray_angle > M_PI && ray_angle > 0)
	{
		y_steps *= -1;
		i = -1;
	}

	x_steps = 32/tan(ray_angle);

	if ((ray_angle < 1.5 * M_PI && ray_angle > M_PI / 2 && x_steps > 0) ||
		((ray_angle > 1.5 * M_PI || ray_angle < M_PI / 2) && x_steps < 0))
		x_steps *= -1;
	while(x_inter > 0 && x_inter < data->x_len * 32 && y_inter+i > 0 && y_inter+i < data->y_len * 32)
	{
		if (wall_hit(data, x_inter, y_inter + i) == -1)
			break;
		if (wall_hit(data, x_inter, y_inter + i) == 1)
		{
			h_found = 1;
			break;
		}
		y_inter += y_steps;
		x_inter += x_steps;
	}
	//////// vertical 
	double vx_inter, vy_inter, vx_steps, vy_steps;
	int v_found,j = 0;

	v_found = 0;

	vx_inter = 32 * floor(data->player.position_x  / 32);
	if ((ray_angle > 1.5 * M_PI || ray_angle < M_PI / 2))
		vx_inter += 32;

	vy_inter = data->player.position_y + (vx_inter - data->player.position_x) * tan(ray_angle);

	vx_steps = 32;
	if (ray_angle < 1.5 * M_PI && ray_angle > M_PI / 2)
	{
		vx_steps *= -1;
		j = -1;
	}
	vy_steps = 32 * tan(ray_angle);
	if ((ray_angle > M_PI && vy_steps > 0) || (ray_angle < M_PI  && ray_angle > 0 && vy_steps < 0)) 
		vy_steps *= -1;

	while(vx_inter +j> 0 && vx_inter +j < data->x_len * 32 && vy_inter > 0 && vy_inter < data->y_len * 32)
	{
		if (wall_hit(data, vx_inter + j, vy_inter) == -1)
			break;
		if (wall_hit(data, vx_inter + j, vy_inter) == 1)
		{
			v_found = 1;
			break;
		}
		vy_inter += vy_steps;
		vx_inter += vx_steps;
	}

	if (h_found)
		h_dist = distance(data->player.position_x, data->player.position_y, x_inter, y_inter);
	else
		h_dist = __INT_MAX__;
	if (v_found)
		v_dist = distance(data->player.position_x, data->player.position_y, vx_inter, vy_inter);
	else
		v_dist = __INT_MAX__;
	
	if (h_dist > v_dist)
	{
		printf("___V___x____%f____y%f\n",vx_inter, vy_inter );
		dda(data,vx_inter, vy_inter);
	}
	else
	{
		printf("x____%f____y%f\n",x_inter, y_inter );
		dda(data,x_inter, y_inter);
	}
}

////////////
int	update(t_data *data)
{
	if (data->i < 1500)
	{
		data->i++;
		return 1;
	}
	else if (data->i == 1500)
		data->i = 0;
	if (data->player.move_u_d == 1)
	{
		data->player.position_x += round(cos(data->player.angle) * 5);
		data->player.position_y += round(sin(data->player.angle) * 5);
	}

	if (data->player.move_u_d == -1)
	{
		data->player.position_x -= round(cos(data->player.angle) * 5);
		data->player.position_y -= round(sin(data->player.angle) * 5);
	}

	if (data->player.moove_r_l == 1)
		data->player.angle += 1 * (M_PI/180);

	if (data->player.moove_r_l == -1)
		data->player.angle -= 1 * (M_PI/180);

	init_img(data);
	player(data->player.position_y, data->player.position_x, data->mlx.l_size, data->mlx.ptr, data);
	mlx_put_image_to_window(data->mlx.mlx,data->mlx.win, data->mlx.img, 0,0);
	data->i++;
	return 1;
}

void	window(t_data *data)
{
	void	*mlx;
	void	*win;
	void	*img;
	int	b_p = 0, l_size = 0, end = 0;
	char	*ptr;

	mlx = NULL;
	data->i = 0;
	data->player.angle =  M_PI;
	data->mlx.mlx = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->x_len * 32, data->y_len * 32, "cub_3d");
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->x_len * 32, data->y_len * 32);
	data->mlx.ptr = mlx_get_data_addr(data->mlx.img, &b_p, &data->mlx.l_size, &end);
	init_img(data);
	player(data->player.position_y, data->player.position_x, data->mlx.l_size, data->mlx.ptr, data);
	mlx_put_image_to_window(data->mlx.mlx,data->mlx.win, data->mlx.img, 0,0);
	mlx_hook(data->mlx.win, 02, 1L<<0, key_press, data);
	mlx_hook(data->mlx.win, 03, 1L<<1 ,key_release, data);
	mlx_loop_hook(data->mlx.mlx, update, data);
	mlx_loop(data->mlx.mlx);
}
