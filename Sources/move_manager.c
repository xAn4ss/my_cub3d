/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:00 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 09:39:08 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void handle_move_x(t_data *data)
{
    if (data->sh.movX == -1)
    {
        int newX = data->sh.x + round(cos(-data->sh.angle - (M_PI / 2))) * (MOVE);
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX;
        int newY = data->sh.y + round(sin(-data->sh.angle - (M_PI / 2))) * (MOVE);
        if (data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
    }
    else if (data->sh.movX == 1)
    {
        int newX = data->sh.x - round(cos(-data->sh.angle - (M_PI / 2))) * (MOVE);
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX; 
        int newY = data->sh.y - round(sin(-data->sh.angle - (M_PI / 2))) * (MOVE);
        if (data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
    }
}

void handle_move_y(t_data *data)
{
    if (data->sh.movY == -1)
    {
        int newX = data->sh.x + round(cos(-data->sh.angle)) * (MOVE);
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX;
        int newY = data->sh.y + round(sin(-data->sh.angle)) * (MOVE);
        if (data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
    }
    if (data->sh.movY == 1)
    {
        int newX = data->sh.x + round(cos(-data->sh.angle + M_PI)) * (MOVE);
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX;
        int newY = data->sh.y + round(sin(-data->sh.angle + M_PI)) * (MOVE);
        if(data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
    }
}

int pressed_key(int num, t_data *data)
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
    return 0;
}

int release_key(int num, t_data *data)
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
    return 0;
}

int update(t_data *data)
{
    // if (data->i < 500)
	// {
	// 	data->i++;
	// 	return 1;
	// }
	// else if (data->i == 500)
	// 	data->i = 0;
    handle_move_x(data);
    handle_move_y(data);
    if (data->sh.rot)
        data->sh.angle -= 3 * (M_PI / 180) * data->sh.rot;
    mlx_clear_window(data->mlx, data->win);
    render_walls(data);
    // data->i++;
    return 1;

}