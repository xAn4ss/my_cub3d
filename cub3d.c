/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoukhart <aoukhart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:04:59 by an4ss             #+#    #+#             */
/*   Updated: 2023/01/06 01:38:06 by aoukhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void    window_grid(void *mlx, void *win, t_data *data)
{
    int len, bpp, endian = 0;
    void *imd = mlx_new_image(data->mlx, 2, data->y_len*42);
    void *imd2 = mlx_new_image(data->mlx, data->x_len*42, 2);
    char *addr = mlx_get_data_addr(imd, &bpp, &len, &endian);
    char *pixel; 
    int y = 0;
    while (y<=data->y_len*42)
    {
        pixel = addr + (y * len + 1 * (bpp / 8));
        *(int*)pixel = 0x105010;
        y++;
    }
    int x = 0;
    while (x <= data->x_len)
    {
        mlx_put_image_to_window(data->mlx, data->win, imd, x*42, 0); 
        x++;
    }
    char *addr2 = mlx_get_data_addr(imd2, &bpp, &len, &endian);
    x = 0;
    while (x<=data->x_len*42)
    {
        pixel = addr2 + (1 * len + x * (bpp / 8));
        *(int*)pixel = 0x105010;
        x++;
    }
    y = 0;
    while (y <= data->y_len)
    {
        mlx_put_image_to_window(data->mlx, data->win, imd2, 0, y*42); 
        y++;
    }
    // for(int i = 0; i < data->x_len + 1; i++)
    // {
    //     for (int y = 0; y < data->y_len*42; y++)
    //         mlx_pixel_put(mlx, win, i*42, y, 0x105010);
    // }
    // for(int i = 0; i < data->y_len + 1; i++)
    // {
    //     for (int y = 0; y < data->x_len*42; y++)
    //         mlx_pixel_put(mlx, win, y, i*42, 0x105010);
    // }
}

void    square(t_data *data, int x, int y, void *mlx, void *win)
{
    ++x;
    ++y;
    int i = x;
    int j = y;

    
    while (i < x+40)
    {
        j = y;
        while(j < y+40)
        {
            mlx_pixel_put(mlx, win, i, j, 0x0000FF);
            j++;
        }
        i++;
    }
}
void    draw_map(t_data *data, void *mlx, void *win)
{
    int x, y = 0;
    while (data->map && data->map[y])
    {
        x = 0;
        while (data->map && data->map[y][x])
        {
            if(data->map[y][x] == '1')
                square(data, x*42, y*42, mlx, win);
            x++;
        }
        y++;
    }
}

/*  DRAW LINE FROM PLAYER'S POSITION TO X,Y*/
void draw_line(t_data *data, double x, double y, int moveX, int moveY, int color)
{
    int dist = sqrt((((double)data->sh.x + x)*((double)data->sh.x + x)) + ((double)data->sh.y + y)*((double)data->sh.y + y));
    double Dx = data->sh.x - x;
    double Dy = data->sh.y - y;
    double Ux = Dx/dist;
    double Uy = Dy/dist;
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

int cast_coll_x(t_data *data, int moveX, int moveY, t_ray *ray)
{
    double nextX, nextY = 0;
    nextY = ray->y/42 * 42;
    if (moveY == 1)
        nextY += 42;
    nextX = ray->x + (ray->y - nextY)/tan(data->sh.angle);
    double Dx,Dy = 0;
    nextY += 2*moveY;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && data->map[(int)floor(nextY/42)][(int)floor(nextX/42)] != '1')
    {
        Dy = 42;
        Dx = 42 / tan(data->sh.angle);
        nextX = nextX - (Dx * moveY);
        nextY = nextY + (Dy * moveY);
    }
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x + nextX)*((double)data->sh.x + nextX)) + ((double)data->sh.y + nextY)*((double)data->sh.y + nextY)));
}

int cast_coll_y(t_data *data, int moveX, int moveY, t_ray *ray)
{
    double nextX, nextY = 0;
    nextX = ray->x/42 * 42;
    if (moveX == 1)
        nextX += 42;
    nextY = ray->y + (ray->x - nextX)*tan(data->sh.angle);
    double Dx,Dy = 0;
    nextX += 2*moveX;
    while (nextX < 42*data->x_len && nextX >= 0 && nextY < 42*data->y_len && nextY >= 0 && data->map[(int)floor(nextY/42)][(int)floor(nextX/42)] != '1')
    {
       Dx = 42;
       Dy = 42 * tan(data->sh.angle);
       nextX = nextX + (Dx * moveX);
       nextY = nextY - (Dy * moveX);
    }
    ray->x = nextX;
    ray->y = nextY;
    return (sqrt((((double)data->sh.x + nextX)*((double)data->sh.x + nextX)) + ((double)data->sh.y + nextY)*((double)data->sh.y + nextY)));
    // return (sqrt(pow(nextX, 2)+pow(nextY, 2)));
}

void cast_ray(t_data * data)
{   
    int dist = 0;
    int moveX, moveY = 0;
    if (data->sh.angle > M_PI/2 && data->sh.angle < M_PI * 3/2)
        moveX = -1;
    else
        moveX = 1;
    if (data->sh.angle > 0 && data->sh.angle < M_PI)
        moveY = -1;
    else
        moveY = 1;
    if (data->sh.angle < 0)
        data->sh.angle = 2*M_PI - 5*M_PI/180;
    else if (data->sh.angle > 2*M_PI - 5*M_PI/180)
        data->sh.angle = 0;
    t_ray rayX;
    t_ray rayY;
    rayY.x = data->sh.x;
    rayY.y = data->sh.y;
    rayX.x = data->sh.x;
    rayX.y = data->sh.y;
    rayX.dist = cast_coll_x(data, moveX, moveY, &rayX);
    rayY.dist = cast_coll_y(data, moveX, moveX, &rayY);
    if (rayX.x <= -2147483648)
        rayX.dist = 2147483647;
    if (rayY.y <= -2147483648)
        rayY.dist = 2147483647;
    printf("(%d,%d)\n", rayX.x, rayX.y);
    printf("(%d,%d)\n", rayY.x, rayY.y);
    printf("x=%d\ny=%d\n", rayX.dist, rayY.dist);
    if (abs(rayX.dist) < abs(rayY.dist))
    {
        dist = rayX.dist;
        draw_line(data, rayX.x, rayX.y, moveX, moveY, 0xFF0000);
    }
    else
    {
        dist = rayY.dist;
        draw_line(data, rayY.x, rayY.y, moveX, moveY, 0x00F000);
    }
}

void cast_rays(t_data *data)
{
    cast_ray(data);

}

void player(t_data *data)
{
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
    char *pixel; 
    int i = 0;
    int y;
    while (i< 5)
    {
        y= 0;
        while (y<5)
        {
            pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
            *(int*)pixel = 0xFFFFFF;
            y++;
        }
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
    cast_rays(data);
    // window_grid(data->mlx, data->win, data);
}

int ched_ched(int num, t_data *data)
{    
    char *pixel; 
    int i = 0;
    double newX = 0;
    double newY = 0;
    // printf("%d__\n", num);
    if (num == 65307)
        exit(1);
    if (num == 113 && data->map && data->map[(data->sh.y)/42][(data->sh.x-2-5)/42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle - (M_PI / 2)) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle - (M_PI / 2)) * 2 * data->sh.mov;
        // printf("&&&%f\n", data->sh.angle);
        player(data);
        // newX = data->sh.x + cos(data->sh.angle) * 100;
        // newY = data->sh.y + sin(data->sh.angle) * 100;
        // draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 122 && data->map[(data->sh.y - 2-5)/42][(data->sh.x+10)/42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle) * 2 * data->sh.mov;
        // printf("&&&%f\n", data->sh.angle);
        player(data);
        // newX = data->sh.x + cos(data->sh.angle) * 100;
        // newY = data->sh.y + sin(data->sh.angle) * 100;
        // draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 100 && data->map[(data->sh.y+10)/42][(data->sh.x + 2+8)/42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle + (M_PI / 2)) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle + (M_PI / 2)) * 2 * data->sh.mov;
        // printf("&&&%f\n", data->sh.angle);
        player(data);
        // newX = data->sh.x + cos(data->sh.angle) * 100;
        // newY = data->sh.y + sin(data->sh.angle) * 100;
        // draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 115 && data->map[(data->sh.y +2+15)/42][(data->sh.x+10)/42] != '1')
    {
        data->sh.mov = -1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.y += sin(data->sh.angle + (M_PI)) * 2 * data->sh.mov;
        data->sh.x += cos(data->sh.angle + (M_PI)) * 2 * data->sh.mov;
        // printf("&&&%f\n", data->sh.angle);
        player(data);
        // newX = data->sh.x + cos(data->sh.angle) * 100;
        // newY = data->sh.y + sin(data->sh.angle) * 100;
        // draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 65363)
    {
        data->sh.rot = -1;
        data->sh.angle += 5 * (M_PI/180) * data->sh.rot * data->sh.mov;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        // printf("&&&%f\n", data->sh.angle);
        player(data);
        // newX = data->sh.x + cos(data->sh.angle) * 100;
        // newY = data->sh.y + sin(data->sh.angle) * 100;
        // draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 65361)
    {
        data->sh.rot = +1;
        data->sh.angle += 5 * (M_PI/180) * data->sh.rot * data->sh.mov;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        // printf("&&&%f\n", data->sh.angle);
        player(data);
        // newX = data->sh.x + cos(data->sh.angle) * 100;
        // newY = data->sh.y + sin(data->sh.angle) * 100;
        // draw_line(data,  newX, newY, 0xFF0000);
    }
    return 0;
}

int walo(t_data *data)
{
    return 0;
}

void    cub3d(t_data *data)
{
    data->sh.x = (data->x_len*42)/2;
    data->sh.y = (data->y_len*42)/2;
    data->sh.angle = M_PI / 2 + M_PI/10;
    data->sh.mov = 1;
    data->sh.rot = 1;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, 42*data->x_len, 42*data->y_len, "kyub_map");
    // void *win2 = mlx_new_window(data->mlx, 100, 100, "test");
    data->img.img = mlx_new_image(data->mlx, 5, 5);
    draw_map(data, data->mlx, data->win);
    player(data);
    // window_grid(data->mlx, data->win, data);
    // draw_line(data, data->sh.x, data->sh.y + 100, 0xFF0000);
    mlx_do_key_autorepeaton(data->mlx);
    // mlx_loop_hook(data->mlx, walo, &data);
    mlx_hook(data->win,2, 1L>>0,ched_ched, data);
    // mlx_hook(data->win,2, 1L>>0,rotate, data);
    /*Delete old player position with key release*/
    mlx_loop(data->mlx);
}