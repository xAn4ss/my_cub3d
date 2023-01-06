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

    
    while (i < x+42)
    {
        j = y;
        while(j < y+42)
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
void draw_line(t_data *data, double x, double y, int color)
{
    int dist = sqrt((((double)data->sh.x + x)*((double)data->sh.x + x)) + ((double)data->sh.y + y)*((double)data->sh.y + y));
    printf("dist : %d\n", dist);
    double Dx = data->sh.x - x;
    double Dy = data->sh.y - y;
    printf("Dx : %f\nDy :%f\n", Dx, Dy);
    double Ux = Dx/dist;
    double Uy = Dy/dist;
    printf("Ux : %f\nUy :%f\n", Ux, Uy);
    double pixX = data->sh.x;
    double pixY = data->sh.y;
    int i = 0;
    while (data->map[(int)pixY/42][(int)pixX/42] != '1')
    {
        mlx_pixel_put(data->mlx, data->win, pixX, pixY, color);
        pixX += Ux;
        pixY += Uy;
        // dist--;
    }
}

void cast_rays(t_data * data)
{
    double x, y = 0;
    double angle = data->sh.angle - (30 * M_PI/180);
    while (angle <= data->sh.angle + (30 * M_PI/180))
    {
        x = data->sh.x + cos(angle) * 100;
        y = data->sh.y + sin(angle) * 100;
        draw_line(data, x, y,0x0000FF);
        angle += M_PI / 180;
    }
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
}

int ched_ched(int num, t_data *data)
{    
    char *pixel; 
    int i = 0;
    double newX = 0;
    double newY = 0;
    printf("%d__\n", num);
    if (num == 0 && data->map && data->map[(data->sh.y)/42][(data->sh.x-2-5)/42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle - (M_PI / 2)) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle - (M_PI / 2)) * 2 * data->sh.mov;
        player(data);
        newX = data->sh.x + cos(data->sh.angle) * 100;
        newY = data->sh.y + sin(data->sh.angle) * 100;
        draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 13 && data->map[(data->sh.y - 2-5)/42][(data->sh.x+10)/42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle) * 2 * data->sh.mov;
        player(data);
        newX = data->sh.x + cos(data->sh.angle) * 100;
        newY = data->sh.y + sin(data->sh.angle) * 100;
        draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 2 && data->map[(data->sh.y+10)/42][(data->sh.x + 2+8)/42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle + (M_PI / 2)) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle + (M_PI / 2)) * 2 * data->sh.mov;
        player(data);
        newX = data->sh.x + cos(data->sh.angle) * 100;
        newY = data->sh.y + sin(data->sh.angle) * 100;
        draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 1 && data->map[(data->sh.y +2+15)/42][(data->sh.x+10)/42] != '1')
    {
        data->sh.mov = -1;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        data->sh.y += sin(data->sh.angle + (M_PI)) * 2 * data->sh.mov;
        data->sh.x += cos(data->sh.angle + (M_PI)) * 2 * data->sh.mov;
        player(data);
        newX = data->sh.x + cos(data->sh.angle) * 100;
        newY = data->sh.y + sin(data->sh.angle) * 100;
        draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 124)
    {
        data->sh.rot = 1;
        data->sh.angle += 5 * (M_PI/180) * data->sh.rot * data->sh.mov;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        player(data);
        printf("%f\n", data->sh.angle);
        newX = data->sh.x + cos(data->sh.angle) * 100;
        newY = data->sh.y + sin(data->sh.angle) * 100;
        draw_line(data,  newX, newY, 0xFF0000);
    }
    else if (num == 123)
    {
        data->sh.rot = -1;
        data->sh.angle += 5 * (M_PI/180) * data->sh.rot * data->sh.mov;
        mlx_clear_window(data->mlx, data->win);
        draw_map(data, data->mlx, data->win);
        player(data);
        printf("%f\n", data->sh.angle);
        newX = data->sh.x + cos(data->sh.angle) * 100;
        newY = data->sh.y + sin(data->sh.angle) * 100;
        draw_line(data,  newX, newY, 0xFF0000);
    }
    return 0;
}

int walo(t_data *data)
{
    return 0;
}

void    cub3d(t_data *data)
{
    t_data *game;
    data->sh.x = (data->x_len*42)/2;
    data->sh.y = (data->y_len*42)/2;
    data->sh.angle = M_PI / 2;
    data->sh.mov = 1;
    data->sh.rot = 1;
    game = data;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, 21*data->x_len, 21*data->y_len, "kyub_map");
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 42*game->x_len, 42*game->y_len, "kyub");
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
    mlx_loop(game->mlx);
}