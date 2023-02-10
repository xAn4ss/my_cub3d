/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:00 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/10 12:19:51 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	handle_move_x(t_data *data)
{
	double new_x;
	double new_y;

	if (data->sh.move_x == -1)
	{
		// new_x = ;
		// new_y = ;
		if (data->map[(int)(data->sh.y + 10*round(sin(-data->sh.angle - (M_PI / 2)))) / 42][(int)(data->sh.x + 10*round(cos(-data->sh.angle - (M_PI / 2))))/ 42] != '1')
		{
			data->sh.x = data->sh.x + (cos(-data->sh.angle - (M_PI / 2)));
			data->sh.y = data->sh.y + (sin(-data->sh.angle - (M_PI / 2)));
		}
	}
	else if (data->sh.move_x == 1)
	{
		if (data->map[(int)(data->sh.y - 10*round(sin(-data->sh.angle - (M_PI / 2)))) / 42][(int)(data->sh.x - 10*round(cos(-data->sh.angle - (M_PI / 2))))/ 42] != '1')
		{
			data->sh.x = data->sh.x - (cos(-data->sh.angle - (M_PI / 2)));
			data->sh.y = data->sh.y - (sin(-data->sh.angle - (M_PI / 2)));
		}
	}
}

void	handle_move_y(t_data *data)
{
	int	new_x;
	int	new_y;

	if (data->sh.move_y == -1)
	{
		if (data->map[(int)(data->sh.y + 10*round(sin(-data->sh.angle))) / 42][(int)(data->sh.x + 10*round(cos(-data->sh.angle))) / 42] != '1')
		{
			data->sh.x += cos(-data->sh.angle)*2;
			data->sh.y += sin(-data->sh.angle)*2;
		}
	}
	if (data->sh.move_y == 1)
	{
		if (data->map[(int)(data->sh.y + 10*round(sin(-data->sh.angle + M_PI))) / 42][(int)(data->sh.x + 10*round(cos(-data->sh.angle + M_PI))) / 42] != '1')
		{
			data->sh.x += cos(-data->sh.angle + M_PI)*2;
			data->sh.y += sin(-data->sh.angle + M_PI)*2;
		}
	}
}

// free
int	pressed_key(int num, t_data *data)
{
	if (num == ECHAP)
		exit(0);
	if (num == LEFT)
		data->sh.move_x = -1;
	else if (num == UP)
		data->sh.move_y = -1;
	else if (num == RIGHT)
		data->sh.move_x = 1;
	else if (num == DOWN)
		data->sh.move_y = 1;
	else if (num == ROT_LEFT)
		data->sh.rot = -1;
	else if (num == ROT_RIGHT)
		data->sh.rot = 1;
	return (0);
}

int	release_key(int num, t_data *data)
{
	if (num == LEFT)
		data->sh.move_x = 0;
	else if (num == UP)
		data->sh.move_y = 0;
	else if (num == RIGHT)
		data->sh.move_x = 0;
	else if (num == DOWN)
		data->sh.move_y = 0;
	else if (num == ROT_LEFT)
		data->sh.rot = 0;
	else if (num == ROT_RIGHT)
		data->sh.rot = 0;
	return (0);
}

int	update(t_data *data)
{
	// if (data->i < 100)
	// {
	// 	data->i++;
	// 	return (1);
	// }
	// else if (data->i == 100)
	// 	data->i = 0;
	handle_move_x(data);
	handle_move_y(data);
	if (data->sh.rot)
		data->sh.angle -= 3 * (M_PI / 180) * data->sh.rot;
	mlx_clear_window(data->mlx, data->win);
	render_walls(data);
	// data->i++;
	return (1);
}
