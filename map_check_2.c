/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:10:27 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 23:17:18 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	p_position(t_data *data, int i, int j)
{
	if (data->map[i][j] == 'N')
	{
		data->spos.n = 1;
		data->sh.x = j * 42 + 21;
		data->sh.y = i * 42 + 21;
	}
	else if (data->map[i][j] == 'S')
	{
		data->spos.s = 1;
		data->sh.x = j * 42 + 21;
		data->sh.y = i * 42 + 21;
	}
	else if (data->map[i][j] == 'E')
	{
		data->spos.e = 1;
		data->sh.x = j * 42 + 21;
		data->sh.y = i * 42 + 21;
	}
	else if (data->map[i][j] == 'W')
	{
		data->spos.w = 1;
		data->sh.x = j * 42 + 21;
		data->sh.y = i * 42 + 21;
	}
	return (1);
}

int	check_map_contenet(t_data *data, int i, int j)
{
	if ((data->spos.n + data->spos.e + data->spos.s + data->spos.w == 1)
		&& (data->map[i][j] == 'W' || data->map[i][j] == 'N'
		|| data->map[i][j] == 'S' || data->map[i][j] == 'E'))
	{
		printf("Error\n\tplayer position problem\n");
		return (0);
	}
	if (!(data->map[i][j] == ' ' || data->map[i][j] == '1'
		|| data->map[i][j] == '0' || data->map[i][j] == 'N'
		|| data->map[i][j] == 'S' || data->map[i][j] == 'E'
		|| data->map[i][j] == 'W'))
	{
		printf("Error\n\tnon supported argument in map\n");
		return (0);
	}
	p_position(data, i, j);
	return (1);
}

int	map_checker_02(t_data *data)
{
	if (!wals_check(data))
	{
		printf("walls problem\n");
		return (0);
	}
	return (1);
}

int	map_checker(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		skip_spaces(data->map[i], &j);
		if (data->map[i][j] != '1'
		|| data->map[i][ft_strlen(data->map[i]) - 1] != '1')
		{
			printf("Error\n\tThe map must be closed/surrounded by walls\n");
			return (0);
		}
		while (data->map[i][j])
		{
			if (!check_map_contenet(data, i, j))
				return (0);
			j++;
		}
		i++;
	}
	if (!map_checker_02(data))
		return (0);
	return (1);
}

int	t_b_check(char *map)
{
	int	i;

	i = 0;
	while (map[i] && (map[i] == ' ' || map[i] == '\t'))
		i++;
	while (map[i])
	{
		if (map[i] && map[i] != ' ' && map[i] != '\t' && map[i] != '1')
			return (0);
		i++;
	}
	return (1);
}
