/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:21:21 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/27 22:32:46 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include"get_next_line.h"
#include"Libft/libft.h"
#include "../mlx.h"
#include <X11/keysym.h>

typedef struct s_sh {
	int x;
	int y;
	
}	t_sh;

typedef struct s_img{
	void *img;
	char *addr;
	int len;
	int bpp;
	int endian;
} t_img;

typedef struct s_data {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map;
	int		x_len;
	int		y_len;
	void	*mlx;
	void	*win;
	t_img	img;
	t_sh 	sh;
	
}	t_data;

int		check_map_name(char *name);
int		check_line(char **line, int x);
int		check_file_content(int fd, t_data *data);
void	white_spaces_skipper(char **str);
int		ft_len(char **tab);
char	**add(char *str, char **data);
void	init_struct(t_data *data);
void	skip_spaces(char *str, int *i);
char	*car_join(char *s1, char c);
void	print_data(t_data *data);

void    cub3d(t_data *data);

#endif
