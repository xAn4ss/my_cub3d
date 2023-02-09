/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:00 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 22:14:50 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	handle_move_x(t_data *data)
{
	int	new_x;
	int	new_y;

	if (data->sh.movX == -1)
	{
		new_x = round(cos(-data->sh.angle - (M_PI / 2))) * (MOVE);
		if (data->map[data->sh.y / 42][(data->sh.x + (new_x * 2)) / 42] != '1')
			data->sh.x += new_x;
		new_y = round(sin(-data->sh.angle - (M_PI / 2))) * (MOVE);
		if (data->map[(data->sh.y + (new_y * 2)) / 42][data->sh.x / 42] != '1')
			data->sh.y += new_y;
	}
	else if (data->sh.movX == 1)
	{
		new_x = round(cos(-data->sh.angle - (M_PI / 2))) * (MOVE);
		if (data->map[data->sh.y / 42][(data->sh.x - (new_x * 2)) / 42] != '1')
			data->sh.x -= new_x;
		new_y = round(sin(-data->sh.angle - (M_PI / 2))) * (MOVE);
		if (data->map[(data->sh.y - (new_y * 2)) / 42][data->sh.x / 42] != '1')
			data->sh.y -= new_y;
	}
}

void	handle_move_y(t_data *data)
{
	int	new_x;
	int	new_y;

	if (data->sh.movY == -1)
	{
		new_x = round(cos(-data->sh.angle)) * (MOVE);
		if (data->map[data->sh.y / 42][(data->sh.x + (new_x * 2)) / 42] != '1')
			data->sh.x += new_x;
		new_y = round(sin(-data->sh.angle)) * (MOVE);
		if (data->map[(data->sh.y + (new_y * 2)) / 42][data->sh.x / 42] != '1')
			data->sh.y += new_y;
	}
	if (data->sh.movY == 1)
	{
		new_x = round(cos(-data->sh.angle + M_PI)) * (MOVE);
		if (data->map[data->sh.y / 42][(data->sh.x + (new_x * 2)) / 42] != '1')
			data->sh.x += new_x;
		new_y = round(sin(-data->sh.angle + M_PI)) * (MOVE);
		if (data->map[(data->sh.y + (new_y * 2)) / 42][data->sh.x / 42] != '1')
			data->sh.y += new_y;
	}
}

int	pressed_key(int num, t_data *data)
{
	printf("-->%d\n", num);
	if (num == ECHAP)
		exit(0);
// free
	if (num == LEFT)
		data->sh.movX = -1;
	else if (num == UP)
		data->sh.movY = -1;
	else if (num == RIGHT)
		data->sh.movX = 1;
	else if (num == DOWN)
		data->sh.movY = 1;
	else if (num == ROT_LEFT)
		data->sh.rot = -1;
	else if (num == ROT_RIGHT)
		data->sh.rot = 1;
	return (0);
}

int	release_key(int num, t_data *data)
{
	if (num == LEFT)
		data->sh.movX = 0;
	else if (num == UP)
		data->sh.movY = 0;
	else if (num == RIGHT)
		data->sh.movX = 0;
	else if (num == DOWN)
		data->sh.movY = 0;
	else if (num == ROT_LEFT)
		data->sh.rot = 0;
	else if (num == ROT_RIGHT)
		data->sh.rot = 0;
	return (0);
}

int	update(t_data *data)
{
	if (data->i < 100)
	{
		data->i++;
		return (1);
	}
	else if (data->i == 100)
		data->i = 0;
	handle_move_x(data);
	handle_move_y(data);
	if (data->sh.rot)
		data->sh.angle -= 3 * (M_PI / 180) * data->sh.rot;
	mlx_clear_window(data->mlx, data->win);
	render_walls(data);
	data->i++;
	return (1);
}
