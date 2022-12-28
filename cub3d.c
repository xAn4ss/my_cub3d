/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: an4ss <an4ss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:04:59 by an4ss             #+#    #+#             */
/*   Updated: 2022/12/27 22:51:32 by an4ss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void    window_grid(void *mlx, void *win, t_data *data)
{
    int len, bpp, endian = 0;
    void *imd = mlx_new_image(data->mlx, 2, data->y_len*32);
    void *imd2 = mlx_new_image(data->mlx, data->x_len*32, 2);
    char *addr = mlx_get_data_addr(imd, &bpp, &len, &endian);
    char *pixel; 
    int y = 0;
    while (y<=data->y_len*32)
    {
        pixel = addr + (y * len + 1 * (bpp / 8));
        *(int*)pixel = 0x105010;
        y++;
    }
    int x = 0;
    while (x <= data->x_len)
    {
        mlx_put_image_to_window(data->mlx, data->win, imd, x*32, 0); 
        x++;
    }
    char *addr2 = mlx_get_data_addr(imd2, &bpp, &len, &endian);
    x = 0;
    while (x<=data->x_len*32)
    {
        pixel = addr2 + (1 * len + x * (bpp / 8));
        *(int*)pixel = 0x105010;
        x++;
    }
    y = 0;
    while (y <= data->y_len)
    {
        mlx_put_image_to_window(data->mlx, data->win, imd2, 0, y*32); 
        y++;
    }
    // for(int i = 0; i < data->x_len + 1; i++)
    // {
    //     for (int y = 0; y < data->y_len*32; y++)
    //         mlx_pixel_put(mlx, win, i*32, y, 0x105010);
    // }
    // for(int i = 0; i < data->y_len + 1; i++)
    // {
    //     for (int y = 0; y < data->x_len*32; y++)
    //         mlx_pixel_put(mlx, win, y, i*32, 0x105010);
    // }
}

void    square(t_data *data, int x, int y, void *mlx, void *win)
{
    ++x;
    ++y;
    int i = x;
    int j = y;

    
    while (i < x+32)
    {
        j = y;
        while(j < y+32)
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
                square(data, x*32, y*32, mlx, win);
            x++;
        }
        y++;
    }
}

void player(t_data *data)
{
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
    char *pixel; 
    int i = 0;
    int y;
    while (i< 10)
    {
        y= 0;
        while (y<10)
        {
            pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
            *(int*)pixel = 0xFF0000;
            y++;
        }
        i++;
    }
    data->sh.x = (data->x_len*32)/2;
    data->sh.y = (data->y_len*32)/2;
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
    
}

int ched_ched(int num, t_data *data)
{    
    char *pixel; 
    int i = 0;
    printf("%d__\n", num);
    if (num == 113 && data->map && data->map[(data->sh.y)/32][(data->sh.x-2-5)/32] != '1')
    {
        mlx_destroy_image(data->mlx, data->img.img);
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        char *pixel; 
        int i = 0;
        int y;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0x00000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
        mlx_destroy_image(data->mlx, data->img.img);
        data->sh.x -= 2;
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        i = 0;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0xFF0000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
    }
    if (num == 122 && data->map[(data->sh.y - 2-5)/32][(data->sh.x+10)/32] != '1')
    {
        mlx_destroy_image(data->mlx, data->img.img);
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        char *pixel; 
        int i = 0;
        int y;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0x00000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
        mlx_destroy_image(data->mlx, data->img.img);
        data->sh.y -= 2;
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        i = 0;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0xFF0000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);

    }
    if (num == 100 && data->map[(data->sh.y+10)/32][(data->sh.x + 2+8)/32] != '1')
    {
        mlx_destroy_image(data->mlx, data->img.img);
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        char *pixel; 
        int i = 0;
        int y;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0x00000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
        mlx_destroy_image(data->mlx, data->img.img);
        data->sh.x += 2;
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        i = 0;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0xFF0000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
    }
    if (num == 115 && data->map[(data->sh.y +2+15)/32][(data->sh.x)/32] != '1')
    {
        mlx_destroy_image(data->mlx, data->img.img);
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        char *pixel; 
        int i = 0;
        int y;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0x00000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
        mlx_destroy_image(data->mlx, data->img.img);
        data->sh.y += 2;
        data->img.img = mlx_new_image(data->mlx, 10, 10);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
        i = 0;
        while (i< 10)
        {
            y= 0;
            while (y<10)
            {
                pixel = data->img.addr + (y * data->img.len + i * (data->img.bpp / 8));
                *(int*)pixel = 0xFF0000;
                y++;
            }
            i++;
        }
        mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);        

    }
}

int walo(t_data *data)
{
    return 0;
}

void    cub3d(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, 850, 450, "kyub");
    draw_map(data, data->mlx, data->win);
    window_grid(data->mlx, data->win, data);
    data->img.img = mlx_new_image(data->mlx, 10, 10);
    player(data);
    // mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    // mlx_put_image_to_window(data->mlx, data->win, data->img, 100, 100);

    mlx_do_key_autorepeaton(data->mlx);
    mlx_loop_hook(data->mlx, walo, &data);
    mlx_hook(data->win,2, 1L>>0,ched_ched, data);
    // mlx_destroy_image(data->mlx, data->img.img);
	printf("salam\n");
    mlx_loop(data->mlx);
}