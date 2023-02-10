/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:22:01 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 23:21:11 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_colors(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3 && str[i])
	{
		if (str[i] == ',')
		{
			j++;
			i++;
			continue ;
		}
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (str[i] || j != 2)
		return (0);
	return (1);
}

int	check_data(t_data *data)
{
	if (!data || !data->c || !data->ea || !data->f || !data->no || !data->so
		|| !data->we || !check_c_f(data) || !data->map || !data->x_len
		|| !data->y_len)
		return (0);
	return (1);
}

int	map_reader(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !check_line(&line, 0))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line[0] != '\n')
	{
		if (ft_strlen(line) - 1 > data->x_len)
			data->x_len = ft_strlen(line) - 1;
		data->map = add(ft_strtrim(line, "\n"), data->map);
		line = get_next_line(fd);
	}
	if (line && line[0] == '\n')
	{
		free(line);
		free_tab(data->map);
		return (0);
	}
	return (1);
}

int	read_cube_file(t_data *data, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	i = 0;
	tab = NULL;
	line = get_next_line(fd);
	while (line && ft_len(tab) < 6)
	{
		if (check_line(&line, 1))
			tab = add(line, tab);
		else
			free(line);
		if (ft_len(tab) < 6)
			line = get_next_line(fd);
	}
	if (!tab || ft_len(tab) != 6)
	{
		free_tab(tab);
		return (0);
	}
	add_to_struct(data, tab);
	return (1);
}

int	check_file_content(int fd, t_data *data)
{
	if (!read_cube_file(data, fd))
		return (0);
	if (!map_reader(data, fd))
		return (0);
	data->y_len = ft_len(data->map);
	if (!check_data(data))
	{
		ft_free(data);
		return (0);
	}
	if (!map_checker(data))
	{
		ft_free(data);
		return (0);
	}
	return (1);
}
//////////////////////////////////////////////////////