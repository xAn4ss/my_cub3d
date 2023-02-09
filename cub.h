/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 17:21:21 by ybachaki          #+#    #+#             */
/*   Updated: 2023/02/09 22:08:03 by aoukhart         ###   ########.fr       */
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
#include"libft.h"
#include "mlx.h"
// #include <X11/keysym.h>
#define SCREEN_W 1080
#define SCREEN_H 720
#define LEFT 0/*113*/
#define UP 13/*122*/
#define RIGHT 2/*100*/
#define DOWN 1/*115*/
#define ECHAP 53/*65307*/
#define ROT_LEFT 123/*65361*/
#define ROT_RIGHT 124/*65363*/
#define MOVE 5
typedef struct s_player {
	int x;
	int y;
	double angle;
	int rot;
	int movX;
	int movY;
	int mov;
}	t_sh;
typedef struct s_spos {
	int	n;
	int	s;
	int	w;
	int	e;
}	t_spos;
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
	int sizeH;
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
	t_spos		spos;
	int i;
}	t_data;

void	draw_background(t_data *data, int floorColor, int ceilColor);
void	draw_shape_x(t_data *data, t_ray ray, int x, t_img wall);
void	draw_shape_y(t_data *data, t_ray ray, int x, t_img wall);
int	pressed_key(int num, t_data *data);
int	release_key(int num, t_data *data);
int	update(t_data *data);
void	draw_wall_n_s(t_data *data, t_ray ray, int wallX);
void	draw_wall_w_e(t_data *data, t_ray ray, int wallX);
void	ft_error(t_data *data);
int	quit(int keycode, t_data *data);
void raycating (t_data *data, t_ray *rayX, t_ray *rayY, int wallX);
void	init_texture(t_data *data);
void	init_angle(t_data *data);
void	init_rays(t_ray rayX, t_ray rayY);
void handle_move_x(t_data *data);
void handle_move_y(t_data *data);
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
int	wals_check(t_data *data);
int	check_colors(char *str);
void render_walls(t_data *data);
int	map_checker(t_data *data);
void	free_tab(char **tab);
int check_c_f(t_data *data);
void    cub3d(t_data data);
void	ft_free(t_data *data);
#endif
