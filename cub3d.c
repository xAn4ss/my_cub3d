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
    nextX = ray->x + (ray->y - nextY)/tan(ray->angle);
    double Dx,Dy = 0;
    nextY += 2*moveY;
    while (nextX < 42*data->x_len && nextX > 0 
        && nextY < 42*data->y_len 
            && data->map[(int)floor(nextY/42)][(int)floor(nextX/42)] != '1')
    {
        Dy = 42;
        Dx = 42 / tan(ray->angle);
        nextX = nextX - (Dx * moveY);
        nextY = nextY + (Dy * moveY);
    }
    nextY -= 2*moveY;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX)*((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY)*((double)data->sh.y - nextY)));
}

int cast_coll_y(t_data *data, int moveX, int moveY, t_ray *ray)
{
    double nextX, nextY = 0;
    nextX = ray->x/42 * 42;
    if (moveX == 1)
        nextX += 42;
    nextY = ray->y + (ray->x - nextX)*tan(ray->angle);
    double Dx,Dy = 0;
    nextX += 2*moveX;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY/42)][(int)floor(nextX/42)] != '1')
    {
       Dx = 42;
       Dy = 42 * tan(ray->angle);
       nextX = nextX + (Dx * moveX);
       nextY = nextY - (Dy * moveX);
    }
    nextX -= 2*moveX;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX)*((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY)*((double)data->sh.y - nextY)));
}

int cast_ray(t_data * data, t_ray rayX, t_ray rayY)
{   
    int dist = 0;
    int moveX, moveY = 0;
    if(rayX.angle < 0)
        rayX.angle = 2*M_PI + rayX.angle;
    else if (rayX.angle > 2*M_PI)
        rayX.angle = -2*M_PI + rayX.angle;
    if(rayY.angle < 0)
        rayY.angle = 2*M_PI + rayY.angle;
    else if (rayY.angle > 2*M_PI)
        rayY.angle = -2*M_PI + rayY.angle;
    if (rayX.angle > M_PI/2 && rayX.angle < M_PI * 3/2)
        moveX = -1;
    else
        moveX = 1;
    if (rayX.angle > 0 && rayX.angle < M_PI)
        moveY = -1;
    else
        moveY = 1;
    rayX.dist = cast_coll_x(data, moveX, moveY, &rayX);
    rayY.dist = cast_coll_y(data, moveX, moveX, &rayY);
    if (rayX.x <= 0)
        rayX.dist = 2147483647;
    if (rayY.y <= 0)
        rayY.dist = 2147483647;
    if (abs(rayX.dist) <= abs(rayY.dist))
        dist = rayX.dist;
    else if(abs(rayX.dist) > abs(rayY.dist))
        dist = rayY.dist;
    return (dist);
}

void draw_shape(t_data *data, int width, int height, int x, int y)
{
    t_img wall;
    int wh = 1;
    wall.img = mlx_xpm_file_to_image(data->mlx, "Wall.xpm", &wh, &wh);
    wall.addr = mlx_get_data_addr(wall.img, &wall.bpp, &wall.len, &wall.endian);
    char *pixel; 
    int i = 0;
    int j;
    int px, py = 0;
    px = x;
    while (i < width)
    {
        j = 0;
        py = y;
        while (j < height)
        {
            ft_memcpy(data->img.addr + (py * data->img.len + px * (data->img.bpp / 8)), 
                wall.addr + ((j*42/height)*wall.len + (x/2)*(wall.bpp/8)), 3);
            // pixel = data->img.addr + (py * data->img.len + px * (data->img.bpp / 8));
            // *(int*)pixel = 0xFFFFFF;
            py++;
            j++;
        }
        px++;
        i++;
    }

}

void cast_rays(t_data *data, t_ray rayX, t_ray rayY)
{
    float dist;
    int sizeH = 0;
    int wallX = 0;
    int moveX, moveY = 0;
    if (data->sh.angle < 0)
        data->sh.angle = 2*M_PI - 5*M_PI/180;
    else if (data->sh.angle > 2*M_PI - 5*M_PI/180)
        data->sh.angle = 0;
    rayY.x = data->sh.x;
    rayY.y = data->sh.y;
    rayX.x = data->sh.x;
    rayX.y = data->sh.y;
    rayX.angle = data->sh.angle - (M_PI/6);
    rayY.angle = data->sh.angle - (M_PI/6);
    while (rayX.angle < data->sh.angle + (M_PI/6))
    {
        dist = cast_ray(data, rayX, rayY);
        sizeH = (SCREEN_H/dist)*70;
        sizeH *= 1/cosf(rayX.angle - data->sh.angle);
            // printf("**%f-->%d\n", (rayX.angle - data->sh.angle)*180/M_PI, sizeH);
        if (sizeH > 0)
        {
            if (sizeH > SCREEN_H)
                sizeH = SCREEN_H;
            draw_shape(data, 3, sizeH, wallX, (SCREEN_H/2) - (sizeH/2));
        }
        rayX.angle += 0.25*M_PI/180;
        rayY.angle += 0.25*M_PI/180;
        wallX += 3;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void player(t_data *data)
{
    t_ray rayX;
    t_ray rayY;
    // mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
    // draw_background(data, get_color(data->f), get_color(data->c));
    // draw_shape(data, 5, 5, data->sh.x, data->sh.y);
    cast_rays(data, rayX, rayY);

    // window_grid(data->mlx, data->win, data);
}
void    render_walls(t_data *data)
{
    t_ray rayX;
    t_ray rayY;
    // mlx_put_image_to_window(data->mlx, data->win, data->img.img, data->sh.x, data->sh.y);
    draw_background(data, get_color(data->f), get_color(data->c));
    cast_rays(data, rayX, rayY);
    // draw_shape(data, 5,5);
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
        data->sh.x -= cos(data->sh.angle - (M_PI / 2)) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle - (M_PI / 2)) * 2 * data->sh.mov;
        render_walls(data);
    }
    else if (num == 122 && data->map[(data->sh.y - 2-5)/42][(data->sh.x+10)/42] != '1')
    {
        data->sh.mov = 1;
        data->sh.x++;
        mlx_clear_window(data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle) * 2 * data->sh.mov;
        render_walls(data);
    }
    else if (num == 100 && data->map[(data->sh.y+10)/42][(data->sh.x + 2+8)/42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        data->sh.x -= cos(data->sh.angle + (M_PI / 2)) * 2 * data->sh.mov;
        data->sh.y -= sin(data->sh.angle + (M_PI / 2)) * 2 * data->sh.mov;
        render_walls(data);
    }
    else if (num == 115 && data->map[(data->sh.y +2+15)/42][(data->sh.x+10)/42] != '1')
    {
        data->sh.mov = -1;
        mlx_clear_window(data->mlx, data->win);
        data->sh.y += sin(data->sh.angle + (M_PI)) * 2 * data->sh.mov;
        data->sh.x += cos(data->sh.angle + (M_PI)) * 2 * data->sh.mov;
        render_walls(data);
    }
    else if (num == 65363)
    {
        data->sh.rot = -1;
        data->sh.angle += 5 * (M_PI/180) * data->sh.rot * data->sh.mov;
        mlx_clear_window(data->mlx, data->win);
        render_walls(data);
    }
    else if (num == 65361)
    {
        data->sh.rot = +1;
        data->sh.angle += 5 * (M_PI/180) * data->sh.rot * data->sh.mov;
        mlx_clear_window(data->mlx, data->win);
        render_walls(data);
    }
    return 0;
}

int get_color(char *s)
{
    char **clrs = ft_split(s, ',');
    int color = 0;
    int i = 0;
    int c = 0;
    int shifter = 23;
    while (i < 3)
    {
        int num = ft_atoi(clrs[i]);
        c = 0;
        while (c < 8)
        {
            if ((num & 1<<c))
                color += 1<<shifter;
            c++;
            shifter--;
        }
        i++;
    }
    return (color);
}

void    draw_background(t_data *data, int floorColor, int ceilColor)
{
    char *pixel;
    int x, y = 0;
    while (y < SCREEN_H/2)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            pixel = data->img.addr + (y * data->img.len + x * (data->img.bpp/8));
            *(int*)pixel = floorColor;
            x++;
        }
        y++;
    }
    y = SCREEN_H/2;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            pixel = data->img.addr + (y * data->img.len + x * (data->img.bpp/8));
            *(int*)pixel = ceilColor;
            x++;
        }
        y++;
    }
}

int walo(t_data *data)
{
    return 0;
}

void    cub3d(t_data *data)
{
    t_img wall;
    int x = 42;
    data->sh.x = (SCREEN_W)/2;
    data->sh.y = (SCREEN_H)/2;
    data->sh.angle = M_PI / 2 + 2*M_PI/10;
    data->sh.mov = 1;
    data->sh.rot = 1;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "kyub_map");
    data->img.img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.len, &data->img.endian);
    render_walls(data);
    // draw_background(data, get_color(data->f), get_color(data->c));
    // wall.img = mlx_xpm_file_to_image(data->mlx, "Wall.xpm", &x, &x);
    // mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    // mlx_put_image_to_window(data->mlx, data->win, wall.img, 0, 0);
    // wall.addr = mlx_get_data_addr(wall.img, &wall.bpp, &wall.len, &wall.endian);
    // int i = 0;
    // int j = 0;
    // char *px_color;
    // t_img test;
    // test.img = mlx_new_image(data->mlx, 100, 100);
    // test.addr = mlx_get_data_addr(test.img, &test.bpp, &test.len, &test.endian);
    // while (i < 3)
    // {
    //     j = 0;
    //     while (j < 100)
    //     {
    //         ft_memcpy(test.addr + (j*test.len + i*(test.bpp/8)),
    //              wall.addr + ((j*42/100)*wall.len + (i*42/100)*(wall.bpp/8)), 3);
    //         // px_color = wall.addr + (j*wall.len + i*(wall.bpp/8));
    //         printf("(%d,%d)\n", i, j);
            
    //         // test.addr[(j*test.len + i*(test.bpp/8))] = px_color;
    //         // printf("(%d,%d)%d\n", i, j, px_color);
    //         // px_color = wall.addr + (j*wall.len + x*(wall.bpp/8));
    //         j++;
    //     } 
    //     i++;
    // }
    // mlx_put_image_to_window(data->mlx, data->win, test.img, 50, 50);
    // mlx_do_key_autorepeaton(data->mlx);
    mlx_hook(data->win,2, 1L>>0,ched_ched, data);
    /*Delete old player position with key release*/
    mlx_loop(data->mlx);
}
