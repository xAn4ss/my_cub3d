/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:26:59 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 23:17:10 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		if ((map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'N'
		|| map[i][j] == 'S' || map[i][j] == 'E') && i != len - 1)
		{
			if (map[i + 1][j] == ' ' || map[i + 1][j] == '\t'
			|| !check_r_l(map[i], j))
				return (0);
		}
		if ((map[i][j] == '0' || map[i][j] == 'W' || map[i][j] == 'N'
		|| map[i][j] == 'S' || map[i][j] == 'E')&& i != 0)
		{
			if (map[i - 1][j] == ' ' || map[i - 1][j] == '\t'
			|| !check_r_l(map[i], j))
				return (0);
		}
		j++;
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

int	wals_check(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len(data->map);
	while (data->map && data->map[i])
	{
		if ((i == 0 || i == len - 1) && !t_b_check(data->map[i]))
			return (0);
		if (i != len - 1 && !len_checker(data->map, i))
			return (0);
		i++;
	}
	i = 0;
	while (data->map && data->map[i])
	{
		if (!check_0(data->map, i, len))
			return (0);
		i++;
	}
	return (1);
}
