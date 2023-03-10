/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybachaki <ybachaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:57:56 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 23:02:21 by ybachaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_map_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '.' && name[i + 1] == 'c' && name[i + 2] == 'u'
			&& name[i + 3] == 'b' && name[i + 4] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("NO = %s\n", data->no);
	printf("SO = %s\n", data->so);
	printf("WE = %s\n", data->we);
	printf("EA = %s\n", data->ea);
	printf("F = %s\n", data->f);
	printf("C = %s\n", data->c);
	printf("x_len = %d\n", data->x_len);
	printf("y_len = %d\n", data->y_len);
	while (data->map && data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("angle = %d\n", data->spos.n);
	printf("angle = %d\n", data->spos.e);
	printf("angle = %d\n", data->spos.s);
	printf("angle = %d\n", data->spos.w);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	init_struct(&data);
	if (argc == 2 && check_map_name(argv[1]))
	{
		fd = open(argv[1], O_RDWR);
		if (fd == -1)
		{
			printf("can't open the file: %s\n", argv[1]);
			exit(1);
		}
		if (!check_file_content(fd, &data))
		{
			printf("EROOR: invalide content\n");
			exit(1);
		}
		print_data(&data);
		cub3d(data);
	}
	return (0);
}
