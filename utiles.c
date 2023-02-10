/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:22:19 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 23:19:05 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**add(char *str, char **tab)
{
	int		i;
	char	**new;

	i = 0;
	new = NULL;
	if (!tab)
	{
		tab = calloc(2, sizeof(char *));
		*tab = str;
		return (tab);
	}
	else
	{
		new = calloc(ft_len(tab) + 2, sizeof(char *));
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
	while (str && (str[*i] == ' ' || str[*i] == '\t'))
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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	ft_free(t_data *data)
{
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->c)
		free(data->c);
	if (data->f)
		free(data->f);
	free_tab(data->map);
}
