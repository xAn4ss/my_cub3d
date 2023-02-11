/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:28:43 by an4ss             #+#    #+#             */
/*   Updated: 2023/02/09 19:53:20 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_texture(t_data *data)
{
	int	x;

	data->txtr.NO.img = mlx_xpm_file_to_image(data->mlx, data->no, &x, &x);
	if (!data->txtr.NO.img)
		ft_error(data);
	data->txtr.NO.addr = mlx_get_data_addr(data->txtr.NO.img,
			&data->txtr.NO.bpp, &data->txtr.NO.len, &data->txtr.NO.endian);
	data->txtr.SO.img = mlx_xpm_file_to_image(data->mlx, data->so, &x, &x);
	if (!data->txtr.SO.img)
		ft_error(data);
	data->txtr.SO.addr = mlx_get_data_addr(data->txtr.SO.img,
			&data->txtr.SO.bpp, &data->txtr.SO.len, &data->txtr.SO.endian);
	data->txtr.EA.img = mlx_xpm_file_to_image(data->mlx, data->ea, &x, &x);
	if (!data->txtr.EA.img)
		ft_error(data);
	data->txtr.EA.addr = mlx_get_data_addr(data->txtr.EA.img,
			&data->txtr.EA.bpp, &data->txtr.EA.len, &data->txtr.EA.endian);
	data->txtr.WE.img = mlx_xpm_file_to_image(data->mlx, data->we, &x, &x);
	if (!data->txtr.WE.img)
		ft_error(data);
	data->txtr.WE.addr = mlx_get_data_addr(data->txtr.WE.img,
			&data->txtr.WE.bpp, &data->txtr.WE.len, &data->txtr.WE.endian);
}

void	init_angle(t_data *data)
{
	if (data->spos.n)
		data->sh.angle = M_PI / 2;
	else if (data->spos.s)
		data->sh.angle = M_PI * 3 / 2;
	else if (data->spos.e)
		data->sh.angle = 0;
	else if (data->spos.w)
		data->sh.angle = M_PI;
}

void	init_rays(t_ray rayX, t_ray rayY)
{
	rayX.angle = fmod(rayX.angle, 2 * M_PI);
	if (rayX.angle < 0)
		rayX.angle += 2 * M_PI;
	rayY.angle = fmod(rayY.angle, 2 * M_PI);
	if (rayY.angle < 0)
		rayY.angle += 2 * M_PI;
	if (rayX.angle > M_PI / 2 && rayX.angle < M_PI * 3 / 2)
		rayX.mov_x = -1;
	else
		rayX.mov_x = 1;
	if (rayX.angle > 0 && rayX.angle < M_PI)
		rayX.mov_y = -1;
	else
		rayX.mov_y = 1;
	rayY.mov_x = rayX.mov_x;
	rayY.mov_y = rayX.mov_y;
}
