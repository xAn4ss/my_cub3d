/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:18:40 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 17:56:31 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->f = NULL;
	data->c = NULL;
	data->map = NULL;
	data->x_len = 0;
	data->y_len = 0;
	data->spos.n = 0;
	data->spos.e = 0;
	data->spos.s = 0;
	data->spos.w = 0;
	data->i = 0;
	data->sh.move_x = 0;
	data->sh.move_y = 0;
	data->sh.rot = 0;	
}

int	ft_len(char **tab)
{
	int	i;

	i = 0;
	if (tab && tab[0])
	{
		while (tab[i])
			i++;
		return (i);
	}
	return (0);
}
