/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:39:00 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/07 18:46:35 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void handle_move_x(t_data *data)
{
    if (data->sh.movX == -1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle - (M_PI / 2))) * 5) / 42][(int)(data->sh.x+round(cos(-data->sh.angle - (M_PI / 2))) * 5) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle - (M_PI / 2))) * 2;
        data->sh.y += round(sin(-data->sh.angle - (M_PI / 2))) * 2;
    }
    else if (data->sh.movX == 1 && 
    data->map[(int)(data->sh.y - round(sin(-data->sh.angle - (M_PI / 2))) * 5) / 42][(int)(data->sh.x-round(cos(-data->sh.angle - (M_PI / 2))) * 5) / 42] != '1')
    {
        data->sh.x -= round(cos(-data->sh.angle - (M_PI / 2))) * 2;
        data->sh.y -= round(sin(-data->sh.angle - (M_PI / 2))) * 2;   
    }
}

void handle_move_y(t_data *data)
{
    if (data->sh.movY == -1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle)) * 5) / 42][(int)(data->sh.x+round(cos(-data->sh.angle)) * 5) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle)) * 2;
        data->sh.y += round(sin(-data->sh.angle)) * 2;
    }
    if (data->sh.movY == 1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle + M_PI)) * 5) / 42][(int)(data->sh.x+round(cos(-data->sh.angle + M_PI)) * 5) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle + M_PI)) * 2;
        data->sh.y += round(sin(-data->sh.angle + M_PI)) * 2; 
    }
}