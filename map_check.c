/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:26:59 by ybachaki          #+#    #+#             */
/*   Updated: 2023/01/27 11:00:37 by ybachaki         ###   ########.fr       */
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
	return 1;
}

int	check_map_contenet(t_data *data, int i, int j)
{
	if ((data->spos.n + data->spos.e + data->spos.s + data->spos.w == 1) &&
		(data->map[i][j] == 'W' || data->map[i][j] == 'N' ||
		data->map[i][j] == 'S' || data->map[i][j] == 'E'))
	{
		printf("Error\n\tplayer position problem\n");
		return (0);
	}
	if (!(data->map[i][j] == ' ' || data->map[i][j] == '1' || data->map[i][j] == '0' || data->map[i][j] == 'N'
		|| data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W'))
	{
		printf("Error\n\tnon supported argument in map\n");
		return (0);
	}
	p_position(data, i, j);
	return (1);
}
////////////////////
int	map_checker(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while(data->map[i][j] && (data->map[i][j] == ' ' || data->map[i][j] == '\t'))
			j++;
		if (data->map[i][j] != '1' || data->map[i][ft_strlen(data->map[i]) - 1] != '1')
		{
			printf("Error\n\tThe map must be closed/surrounded by walls\n");
			return (0);
		}
		while(data->map[i][j])
		{
			if (!check_map_contenet(data, i, j))
				return (0);
			j++;
		}
		i++;
	}
	if (!wals_check(data))
	{
		printf("walls problem\n");
		return (0);
	}
	return (1);
}
//////////////////////
int	t_b_check(char *map)
{
	int	i;

	i = 0;
	while (map[i] && (map[i] == ' ' || map[i] == '\t'))
		i++;
	while(map[i])
	{
		if (map[i] && map[i] != ' ' && map[i] != '\t' && map[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_1(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\t' )
			return (0);
		i++;
	}
	return (1);
}

int	len_checker(char **map, int i)
{
	int	len;

	len = ft_strlen(map[i]) - ft_strlen(map[i + 1]);
	if (len > 0)
	{
		if (!check_1(map[i] + ft_strlen(map[i + 1])))
			return (0);
	}
	else if (len < 0)
	{
		if (!check_1(map[i + 1] + ft_strlen(map[i])))
			return (0);
	}
	return (1);
}

int	check_r_l(char *str, int i)
{
	if (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		return (0);
	if (i < ft_strlen(str) - 1 && (str[i + 1] == ' ' || str[i + 1] == '\t'))
		return (0);
	return (1);
}

int	check_0(char **map, int i, int len)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == '0' && i != len - 1)
		{
			if (map[i + 1][j] == ' ' || map[i + 1][j] == '\t'
			|| !check_r_l(map[i], j))
				return (0);
		}
		if (map[i][j] == '0' && i != 0)
		{
			if (map[i - 1][j] == ' ' || map[i - 1][j] == '\t'
			|| !check_r_l(map[i], j))
				return (0);
		}
		j++;
	}
	return (1);
}

int	wals_check(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len(data->map);
	while(data->map && data->map[i])
	{
		if ((i == 0 || i == len - 1) && !t_b_check(data->map[i]))
			return (0);
		if (i != len - 1 && !len_checker(data->map, i))
			return (0);
		i++;
	}
	i = 0;
	while(data->map && data->map[i])
	{
		if (!check_0(data->map, i, len))
			return (0);
		i++;
	}
	return (1);
}
