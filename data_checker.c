/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:22:01 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/26 00:11:57 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_line(char **line, int x)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while ((line[0][i] == ' ' || line[0][i] == '\t') && x)
		i++;
	if (line[0][i] == '\n' || line[0][i] == '\0')
		return (0);
	new = strdup(*line + i);
	free (*line);
	*line = new;
	return (1);
}

char	*add_after_split(char *str, int i)
{
	int		n_spaces;
	char	*temp;

	n_spaces = 0;
	temp = NULL;
	while (str && str[i] && str[i] != '\n')
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			skip_spaces(str, &i);
			if (str[i] != '\0' && str[i] != '\n')
				n_spaces++;
			continue;
		}
		temp = car_join(temp, str[i]);
		i++;
	}
	if (n_spaces != 1)
		return (NULL);
	return (temp);

}
void	add_to_struct(t_data *data, char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		if (strncmp("NO ", tab[i], 3) == 0)
			data->no = add_after_split(tab[i], 2);
		else if (strncmp("SO ", tab[i], 3) == 0)
			data->so = add_after_split(tab[i], 2);
		else if (strncmp("WE ", tab[i], 3) == 0)
			data->we = add_after_split(tab[i], 2);
		else if (strncmp("EA ", tab[i], 3) == 0)
			data->ea = add_after_split(tab[i], 2);
		else if (strncmp("F ", tab[i], 1) == 0)
			data->f = add_after_split(tab[i], 1);
		else if (strncmp("C ", tab[i], 1) == 0)
			data->c = add_after_split(tab[i], 1);
		i++;
	}
	// must free **tab
}

int	check_c_f(t_data *data)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp =NULL;
	temp = ft_split(data->c, ',');
	while (j < 2)
	{
		if (ft_len(temp) != 3)
			return (0);
		else
			while (temp && temp[i])
			{
				if (ft_atoi(temp[i]) > 255 || ft_atoi(temp[i]) < 0)
					return (0);
				i++;
			}
		j++;
		i = 0;
		temp = ft_split(data->f, ',');
	}
	return (1);
}

int	check_data(t_data *data)
{
	if (!data || !data->c || !data->ea || !data->f
	|| !data->no || !data->so || !data->we || !check_c_f(data) || !data->map
	|| !data->x_len || !data->y_len)
		return (0);
	return (1);
}

int	map_reader(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line && !check_line(&line, 0))
		line = get_next_line(fd);

	while(line && line[0] != '\n')
	{
		i++;
		if (ft_strlen(line) - 1 > data->x_len)
			data->x_len = ft_strlen(line) - 1;
		data->map = add(line, data->map);
		line = get_next_line(fd);
	}
	if (line && line[0] == '\n')
		return (0);
	data->y_len = i;
	return (1);
}

int	check_file_content(int fd, t_data *data)
{
	char 	*line;
	char	**tab;
	int		i;

	i = 0;
	tab = NULL;
	line = NULL;
	line = get_next_line(fd);
	while (line && ft_len(tab) < 6)
	{
		if (check_line(&line, 1) && isalpha(line[0]))
			tab = add(line, tab);
		else
			free(line);
		if (ft_len(tab) < 6)
			line = get_next_line(fd);
	}
	if (ft_len(tab) != 6)
	{
		// free
		return (0);
	}
	add_to_struct(data, tab);
	
	if (!map_reader(data, fd))
		return (0);
	
	if (!check_data(data))
		return(0);

	return (1);
}
