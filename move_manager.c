/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:00 by an4ss             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/09 02:41:19 by aoukhart         ###   ########.fr       */
=======
/*   Updated: 2023/02/08 10:25:51 by an4ss            ###   ########.fr       */
>>>>>>> 3f910fb (pull)
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void handle_move_x(t_data *data)
{
<<<<<<< HEAD
    if (data->sh.movX == -1 /*&& 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle - (M_PI / 2))) * MOVE+2) / 42][(int)(data->sh.x+round(cos(-data->sh.angle - (M_PI / 2))) * MOVE+2) / 42] != '1'*/)
    {
        int newX = data->sh.x + round(cos(-data->sh.angle - (M_PI / 2))) * MOVE;
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX;
        int newY = data->sh.y + round(sin(-data->sh.angle - (M_PI / 2))) * MOVE;
        if (data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
    }
    else if (data->sh.movX == 1 /*&& 
    data->map[(int)(data->sh.y - round(sin(-data->sh.angle - (M_PI / 2))) * MOVE+2) / 42][(int)(data->sh.x-round(cos(-data->sh.angle - (M_PI / 2))) * MOVE+2) / 42] != '1'*/)
    {
        int newX = data->sh.x - round(cos(-data->sh.angle - (M_PI / 2))) * MOVE;
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX;
        int newY = data->sh.y - round(sin(-data->sh.angle - (M_PI / 2))) * MOVE;
        if (data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
=======
    int mov;

    mov = 4;
    if (data->sh.movX == -1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle - (M_PI / 2))) * 6) / 42][(int)(data->sh.x+round(cos(-data->sh.angle - (M_PI / 2))) * 6) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle - (M_PI / 2))) * mov;
        data->sh.y += round(sin(-data->sh.angle - (M_PI / 2))) * mov;
    }
    else if (data->sh.movX == 1 && 
    data->map[(int)(data->sh.y - round(sin(-data->sh.angle - (M_PI / 2))) * 6) / 42][(int)(data->sh.x-round(cos(-data->sh.angle - (M_PI / 2))) * 6) / 42] != '1')
    {
        data->sh.x -= round(cos(-data->sh.angle - (M_PI / 2))) * mov;
        data->sh.y -= round(sin(-data->sh.angle - (M_PI / 2))) * mov;   
>>>>>>> 3f910fb (pull)
    }
}

void handle_move_y(t_data *data)
{
<<<<<<< HEAD
    if (data->sh.movY == -1 /*&& 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle)) * MOVE+2) / 42][(int)(data->sh.x+round(cos(-data->sh.angle)) * MOVE+2) / 42] != '1'*/)
    {
        int newX = data->sh.x + round(cos(-data->sh.angle)) * MOVE;
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX;
        int newY = data->sh.y + round(sin(-data->sh.angle)) * MOVE;
        if (data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
    }
    if (data->sh.movY == 1 /*&& 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle + M_PI)) * MOVE+2) / 42][(int)(data->sh.x+round(cos(-data->sh.angle + M_PI)) * MOVE+2) / 42] != '1'*/)
    {
        int newX = data->sh.x+round(cos(-data->sh.angle + M_PI)) * MOVE;
        if (data->map[data->sh.y/42][newX/42] != '1')
            data->sh.x = newX;
        int newY = data->sh.y + round(sin(-data->sh.angle + M_PI)) * MOVE;
        if(data->map[newY/42][data->sh.x/42] != '1')
            data->sh.y = newY;
=======
    int mov;

    mov = 4;
    if (data->sh.movY == -1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle)) * 6) / 42][(int)(data->sh.x+round(cos(-data->sh.angle)) * 6) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle)) * mov;
        data->sh.y += round(sin(-data->sh.angle)) * mov;
    }
    if (data->sh.movY == 1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle + M_PI)) * 6) / 42][(int)(data->sh.x+round(cos(-data->sh.angle + M_PI)) * 6) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle + M_PI)) * mov;
        data->sh.y += round(sin(-data->sh.angle + M_PI)) * mov; 
>>>>>>> 3f910fb (pull)
    }
}