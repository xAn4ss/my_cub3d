/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:21:21 by ybachaki          #+#    #+#             */
/*   Updated: 2022/12/30 03:24:13 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include"get_next_line.h"
#include"Libft/libft.h"
#include "../minilibx-linux-master/mlx.h"
// #include <X11/keysym.h>
#define SCREEN_W 720
#define SCREEN_H 480
typedef struct s_sh {
	int x;
	int y;
	double angle;
	int rot;
	int movX;
	int movY;
	int mov;
}	t_sh;

typedef struct s_img{
	void *img;
	char *addr;
	int len;
	int bpp;
	int endian;
} t_img;

typedef struct s_txt{
	t_img NO;
	t_img SO;
	t_img WE;
	t_img EA;
}	t_txt;


typedef struct s_ray{
	int x;
	int y;
	double dist;
	double angle;
	int moveX;
	int moveY;
} t_ray;

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
	t_txt	txtr;
	int i;
}	t_data;

int get_color(char *s);
void    draw_background(t_data *data, int floorColor, int ceilColor);
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
void draw_shape(t_data *data, int height, int x, int pixelX, t_img wall);


void    cub3d(t_data data);

#endif
