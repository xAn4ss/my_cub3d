/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:22:19 by ybachaki          #+#    #+#             */
/*   Updated: 2023/01/22 02:45:25 by ybachaki         ###   ########.fr       */
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
}

int	ft_len(char **tab)
{
	int	i;

	i = 0;
	if (tab && tab[0])
	{
		while(tab[i])
			i++;
		return (i);
	}
	return (0);
}

char	**add(char *str, char **tab)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	if (!tab)
	{
		tab = calloc(2, sizeof(char*));
		*tab = str;
		return (tab);
	}
	else
	{
		new = calloc(ft_len(tab) + 2, sizeof(char*));
		while (tab[i])
		{
			new[i] = tab[i];
			i++;
		}
		new[i] = str;
		free(tab);
		return (new);
	}
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}

char	*car_join(char *s1, char c)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (c == '\0')
		return (s1);
	res = ft_calloc(ft_strlen(s1) + 2, 1);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	free(s1);
	return (res);
}
