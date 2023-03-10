/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checker_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:21:02 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 23:21:16 by ybachaki         ###   ########.fr       */
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
	free(*line);
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
			continue ;
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
	while (tab[i])
	{
		if (strncmp("NO ", tab[i], 3) == 0 || strncmp("NO\t", tab[i], 3) == 0)
			data->no = add_after_split(tab[i], 2);
		else if (strncmp("SO ", tab[i], 3) == 0
			|| strncmp("SO\t", tab[i], 3) == 0)
			data->so = add_after_split(tab[i], 2);
		else if (strncmp("WE ", tab[i], 3) == 0
			|| strncmp("WE\t", tab[i], 3) == 0)
			data->we = add_after_split(tab[i], 2);
		else if (strncmp("EA ", tab[i], 3) == 0
			|| strncmp("EA\t", tab[i], 3) == 0)
			data->ea = add_after_split(tab[i], 2);
		else if (strncmp("F ", tab[i], 1) == 0 || strncmp("F\t", tab[i], 1) == 0)
			data->f = add_after_split(tab[i], 1);
		else if (strncmp("C ", tab[i], 1) == 0 || strncmp("C\t", tab[i], 1) == 0)
			data->c = add_after_split(tab[i], 1);
		i++;
	}
	free_tab(tab);
}

int	check_len(char *str)
{
	char	**temp;
	int		i;

	i = 0;
	temp = 0;
	temp = ft_split(str, ',');
	if (!temp || ft_len(temp) != 3)
	{
		free_tab(temp);
		return (0);
	}
	while (temp && temp[i])
	{
		if (ft_atoi(temp[i]) > 255 || ft_atoi(temp[i]) < 0)
		{
			free_tab(temp);
			return (0);
		}
		i++;
	}
	free_tab(temp);
	return (1);
}

int	check_c_f(t_data *data)
{
	if (!check_colors(data->f) || !check_colors(data->c))
		return (0);
	if (!check_len(data->c) || !check_len(data->f))
		return (0);
	return (1);
}
