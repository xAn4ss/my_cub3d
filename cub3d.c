/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:04:59 by an4ss             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/09 02:04:33 by aoukhart         ###   ########.fr       */
=======
/*   Updated: 2023/02/08 10:20:52 by an4ss            ###   ########.fr       */
>>>>>>> 3f910fb (pull)
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void square(t_data *data, int x, int y, void *mlx, void *win)
{
    ++x;
    ++y;
    int i = x;
    int j = y;

    while (i < x + 38)
    {
        j = y;
        while (j < y + 38)
        {
            mlx_pixel_put(mlx, win, i, j, 0x0000FF);
            j++;
        }
        i++;
    }
}

void draw_map(t_data *data)
{
    int x, y = 0;
    while (data->map && data->map[y])
    {
        x = 0;
        while (data->map && data->map[y][x])
        {
            if (data->map[y][x] == '1')
                square(data, x * 42, y * 42, data->mlx, data->win);
            x++;
        }
        y++;
    }
}

/*  DRAW LINE FROM PLAYER'S POSITION TO X,Y*/
void draw_line(t_data *data, double x, double y, int moveX, int moveY, int color)
{
    int dist = sqrt((((double)data->sh.x + x) * ((double)data->sh.x + x)) + ((double)data->sh.y + y) * ((double)data->sh.y + y));
    double Dx = data->sh.x - x;
    double Dy = data->sh.y - y;
    double Ux = Dx / dist;
    double Uy = Dy / dist;
    double pixX = data->sh.x;
    double pixY = data->sh.y;
    int i = 0;
    while (dist && dist < 2147483647 && dist > 0)
    {
        mlx_pixel_put(data->mlx, data->win, pixX, pixY, color);
        pixX -= Ux;
        pixY -= Uy;
        dist--;
    }
}

double cast_coll_x(t_data *data, t_ray *ray)
{
    double nextX, nextY = 0;
    nextY = ray->y / 42 * 42;
    if (ray->moveY == 1)
        nextY += 42;
    nextX = ray->x + (ray->y - nextY) / tan(ray->angle);
    double Dx, Dy = 0;
    nextY += 2 * ray->moveY;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dy = 42;
        Dx = 42 / tan(ray->angle);
        nextX = nextX - (Dx * ray->moveY);
        nextY = nextY + (Dy * ray->moveY);
    }
    nextY -= 2 * ray->moveY;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX) * ((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY) * ((double)data->sh.y - nextY)));
}

double cast_coll_y(t_data *data, t_ray *ray)
{

    double nextX, nextY = 0;
    nextX = ray->x / 42 * 42;
    if (ray->moveX == 1)
        nextX += 42;
    nextY = ray->y + (ray->x - nextX) * tan(ray->angle);
    double Dx, Dy = 0;
    nextX += 2 * ray->moveX;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dx = 42;
        Dy = 42 * tan(ray->angle);
        nextX = nextX + (Dx * ray->moveX);
        nextY = nextY - (Dy * ray->moveX);
    }
    nextX -= 2 * ray->moveX;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX) * ((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY) * ((double)data->sh.y - nextY)));
}

void draw_wall_N_S(t_data *data, t_ray ray, int wallX)
{
    int x = 0;
    t_img NO_SO;
    if (ray.angle < M_PI && ray.angle >= 0)
        NO_SO = data->txtr.NO;
    else
        NO_SO = data->txtr.SO;
    int sizeH = (SCREEN_H / ray.dist) * 70;
    sizeH *= 1 / cosf(ray.angle - data->sh.angle);
    if (sizeH > 0)
        draw_shape(data, sizeH, wallX, ray.x, NO_SO);
}

void draw_wall_W_E(t_data *data, t_ray ray, int wallX)
{
    int x = 0;
    t_img W_E;
    if((ray.angle >= 0.5* M_PI && ray.angle < 1.5 * M_PI))
        W_E = data->txtr.WE;
    else
        W_E = data->txtr.EA;
    int sizeH = (SCREEN_H / ray.dist) * 70;
    sizeH *= 1 / cosf(ray.angle - data->sh.angle);
    if (sizeH > 0)
        draw_shape(data, sizeH, wallX, ray.y, W_E);
}

void init_rays(t_ray rayX, t_ray rayY)
{
    rayX.angle = fmod(rayX.angle, 2*M_PI);
    if (rayX.angle < 0)
        rayX.angle += 2 * M_PI;
    rayY.angle = fmod(rayY.angle, 2*M_PI);
    if (rayY.angle < 0)
        rayY.angle += 2 * M_PI;
    if (rayX.angle > M_PI / 2 && rayX.angle < M_PI * 3 / 2)
        rayX.moveX = -1;
    else
        rayX.moveX = 1;
    if (rayX.angle > 0 && rayX.angle < M_PI)
        rayX.moveY = -1;
    else
        rayX.moveY = 1;
    rayY.moveX = rayX.moveX;
    rayY.moveY = rayX.moveY;
}

void raycating (t_data *data, t_ray *rayX, t_ray *rayY, int wallX)
{
    rayX->dist = cast_coll_x(data, rayX);
    rayY->dist = cast_coll_y(data, rayY);
    if (rayX->x <= 0)
        rayX->dist = 2147483647;
    if (rayY->y <= 0)
        rayY->dist = 2147483647;
    if (rayX->dist < rayY->dist)
        draw_wall_N_S(data, *rayX, wallX);
    else if (rayX->dist > rayY->dist)
        draw_wall_W_E(data, *rayY, wallX);
}

void cast_ray(t_data *data, int wallX, t_ray rayX, t_ray rayY)
{
    t_ray ray;
    int dist = 0;
    int moveX, moveY = 0;
       rayX.angle = fmod(rayX.angle, 2*M_PI);
    if (rayX.angle < 0)
        rayX.angle += 2 * M_PI;
    rayY.angle = fmod(rayY.angle, 2*M_PI);
    if (rayY.angle < 0)
        rayY.angle += 2 * M_PI;
    if (rayX.angle > M_PI / 2 && rayX.angle < M_PI * 3 / 2)
        rayX.moveX = -1;
    else
        rayX.moveX = 1;
    if (rayX.angle > 0 && rayX.angle < M_PI)
        rayX.moveY = -1;
    else
        rayX.moveY = 1;
    rayY.moveX = rayX.moveX;
    rayY.moveY = rayX.moveY;
    raycating(data, &rayX, &rayY, wallX);
}

void draw_shape(t_data *data, int height, int x, int pixelX, t_img wall)
{
    char *pixel;
    int i = 0;
    wall.addr = mlx_get_data_addr(wall.img, &wall.bpp, &wall.len, &wall.endian);
    int j;
    int y = (SCREEN_H / 2) - (height / 2);
    int px, py = 0;
    px = x;
    while (i < 1)
    {
        j = 0;
        py = y;
        while (j < height)
        {
            if (py >= 0 && py < SCREEN_H)
            {
                ft_memcpy(data->img.addr + (py * data->img.len + px * (data->img.bpp / 8)),
                      wall.addr + ((j*42/height) * wall.len + (pixelX % 42) * (wall.bpp / 8)), 3);
            }
            py++;
            j++;
        }
        px++;
        i++;
    }
}

void process_game(t_data *data, t_ray rayX, t_ray rayY)
{
    int wallX = 0;
    rayY.x = (double)data->sh.x;
    rayY.y = (double)data->sh.y;
    rayX.x = (double)data->sh.x;
    rayX.y = (double)data->sh.y;
    rayX.angle = data->sh.angle - (M_PI / 6);
    rayY.angle = data->sh.angle - (M_PI / 6);
    wallX = SCREEN_W;
    while (rayX.angle < data->sh.angle + (M_PI / 6) && wallX > 0)
    {
        wallX -= 1;
        cast_ray(data, wallX, rayX, rayY);
<<<<<<< HEAD
        rayX.angle += 0.055 * M_PI / 180;
        rayY.angle += 0.055 * M_PI / 180;
=======
        rayX.angle += 0.08 * M_PI / 180;
        rayY.angle += 0.08 * M_PI / 180;
        printf("%d\n", wallX);
>>>>>>> 3f910fb (pull)
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

// void player(t_data *data)
// {
//     t_ray rayX;
//     t_ray rayY;
//     cast_rays(data, rayX, rayY);

// }
void render_walls(t_data *data)
{
    t_ray rayX;
    t_ray rayY;
	
    data->sh.angle = fmod(data->sh.angle , (2 * M_PI));
	if (data->sh.angle < 0)
		data->sh.angle += 2 * M_PI;
    draw_background(data, get_color(data->f), get_color(data->c));
    process_game(data, rayX, rayY);
}

int get_color(char *s)
{
    char **clrs = ft_split(s, ',');
    int color = 0;
    int i = 0;
    int p = 2;
    while (i < 3)
    {
        color += ft_atoi(clrs[i]) * pow(256, p);
        p--;
        i++;
    }
    return (color);
}

void draw_background(t_data *data, int floorColor, int ceilColor)
{
    char *pixel;
    int x, y = -1;
    while (++y < SCREEN_H / 2)
    {
        x = -1;
        while (++x < SCREEN_W)
        {
            pixel = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
            *(int *)pixel = ceilColor;
        }
    }
    y = SCREEN_H / 2 - 1;
    while (++y < SCREEN_H)
    {
        x = -1;
        while (++x < SCREEN_W)
        {
            pixel = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
            *(int *)pixel = floorColor;
        }
    }
}

int pressed_key(int num, t_data *data)
{
    printf("-->%d\n", num);
    if (num == ECHAP)
        exit(0);
        // free
    if (num == LEFT)
        data->sh.movX = -1;
    else if (num == UP)
        data->sh.movY = -1;
    else if (num == RIGHT)
        data->sh.movX = 1;
    else if (num == DOWN)
        data->sh.movY = 1;
    else if (num == ROT_LEFT)
        data->sh.rot = -1;
    else if (num == ROT_RIGHT)
        data->sh.rot = 1;
    return 0;
}

int release_key(int num, t_data *data)
{
    if (num == LEFT)
        data->sh.movX = 0;
    else if (num == UP)
        data->sh.movY = 0;
    else if (num == RIGHT)
        data->sh.movX = 0;
    else if (num == DOWN)
        data->sh.movY = 0;
    else if (num == ROT_LEFT)
        data->sh.rot = 0;
    else if (num == ROT_RIGHT)
        data->sh.rot = 0;
    return 0;
}

int update(t_data *data)
{
    // if (data->i < 500)
	// {
	// 	data->i++;
	// 	return 1;
	// }
	// else if (data->i == 500)
	// 	data->i = 0;
    handle_move_x(data);
    handle_move_y(data);
    if (data->sh.rot)
        data->sh.angle -= 3 * (M_PI / 180) * data->sh.rot;
    mlx_clear_window(data->mlx, data->win);
    render_walls(data);
    // data->i++;
    return 1;

}
void ft_error(t_data *data)
{
    printf("somethin's wrong with text_file -_-\n");
    exit(EXIT_FAILURE);
}

void init_texture(t_data *data)
{
    int x;
    data->txtr.NO.img =  mlx_xpm_file_to_image(data->mlx, data->no, &x, &x);
    if (!data->txtr.NO.img)
        ft_error(data);
    data->txtr.NO.addr = mlx_get_data_addr(data->txtr.NO.img, &data->txtr.NO.bpp, &data->txtr.NO.len, &data->txtr.NO.endian);

    data->txtr.SO.img =  mlx_xpm_file_to_image(data->mlx, data->so, &x, &x);
    if (!data->txtr.SO.img)
        ft_error(data);
    data->txtr.SO.addr = mlx_get_data_addr(data->txtr.SO.img, &data->txtr.SO.bpp, &data->txtr.SO.len, &data->txtr.SO.endian);
    
    data->txtr.EA.img =  mlx_xpm_file_to_image(data->mlx, data->ea, &x, &x);
    if (!data->txtr.EA.img)
        ft_error(data);
    data->txtr.EA.addr = mlx_get_data_addr(data->txtr.EA.img, &data->txtr.EA.bpp, &data->txtr.EA.len, &data->txtr.EA.endian);

    data->txtr.WE.img =  mlx_xpm_file_to_image(data->mlx, data->we, &x, &x);
    if (!data->txtr.WE.img)
        ft_error(data);
    data->txtr.WE.addr = mlx_get_data_addr(data->txtr.WE.img, &data->txtr.WE.bpp, &data->txtr.WE.len, &data->txtr.WE.endian);
}
void    init_angle(t_data *data)
{
    if (data->spos.n)
        data->sh.angle = M_PI/2;
    else if (data->spos.s)
        data->sh.angle = M_PI*3/2;
    else if (data->spos.e)
        data->sh.angle = 0;
    else if (data->spos.w)
        data->sh.angle = M_PI;
}

void check_text_files(t_data *data)
{
    if (open(data->no, O_RDONLY) == -1||
        open(data->ea, O_RDONLY) == -1 ||
            open(data->so, O_RDONLY) == -1 ||
                open(data->we, O_RDONLY) == -1)
    {
        printf("Test file not found-_-\n");
        exit(EXIT_FAILURE);
    }

    init_texture(data);
    init_angle(data);
}
int	quit(int keycode, t_data *data)
{
        // should free;
        exit(0);
}

void cub3d(t_data data)
{
    check_text_files(&data);
    data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "kyub_map");
    data.img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
    data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.len, &data.img.endian);
    render_walls(&data);
    mlx_hook(data.win, 17, 1L << 2, &quit, &data);
    mlx_hook(data.win, 2, 1L<<0, pressed_key, &data);
    mlx_hook(data.win, 3, 1L<<1, release_key, &data);
    mlx_loop_hook(data.mlx, update, &data);
    /*Delete old player position with key release*/
 
    mlx_loop(data.mlx);
}










