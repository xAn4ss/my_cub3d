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

void window_grid(void *mlx, void *win, t_data *data)
{
    int len, bpp, endian = 0;
    void *imd = mlx_new_image(data->mlx, 2, data->y_len * 42);
    void *imd2 = mlx_new_image(data->mlx, data->x_len * 42, 2);
    char *addr = mlx_get_data_addr(imd, &bpp, &len, &endian);
    char *pixel;
    int y = 0;
    while (y <= data->y_len * 42)
    {
        pixel = addr + (y * len + 1 * (bpp / 8));
        *(int *)pixel = 0x105010;
        y++;
    }
    int x = 0;
    while (x <= data->x_len)
    {
        mlx_put_image_to_window(data->mlx, data->win, imd, x * 42, 0);
        x++;
    }
    char *addr2 = mlx_get_data_addr(imd2, &bpp, &len, &endian);
    x = 0;
    while (x <= data->x_len * 42)
    {
        pixel = addr2 + (1 * len + x * (bpp / 8));
        *(int *)pixel = 0x105010;
        x++;
    }
    y = 0;
    while (y <= data->y_len)
    {
        mlx_put_image_to_window(data->mlx, data->win, imd2, 0, y * 42);
        y++;
    }
}

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

double cast_coll_x(t_data *data, int moveX, int moveY, t_ray *ray)
{
    double nextX, nextY = 0;
    nextY = ray->y / 42 * 42;
    if (moveY == 1)
        nextY += 42;
    nextX = ray->x + (ray->y - nextY) / tan(ray->angle);
    double Dx, Dy = 0;
    nextY += 2 * moveY;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dy = 42;
        Dx = 42 / tan(ray->angle);
        nextX = nextX - (Dx * moveY);
        nextY = nextY + (Dy * moveY);
    }
    nextY -= 2 * moveY;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX) * ((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY) * ((double)data->sh.y - nextY)));
}

double cast_coll_y(t_data *data, int moveX, int moveY, t_ray *ray)
{

    double nextX, nextY = 0;
    nextX = ray->x / 42 * 42;
    if (moveX == 1)
        nextX += 42;
    nextY = ray->y + (ray->x - nextX) * tan(ray->angle);
    double Dx, Dy = 0;
    nextX += 2 * moveX;
    while (nextX < 42*data->x_len && nextX > 0 && nextY < 42*data->y_len && nextY > 0 && data->map[(int)floor(nextY / 42)][(int)floor(nextX / 42)] != '1')
    {
        Dx = 42;
        Dy = 42 * tan(ray->angle);
        nextX = nextX + (Dx * moveX);
        nextY = nextY - (Dy * moveX);
    }
    nextX -= 2 * moveX;
    ray->x = (int)nextX;
    ray->y = (int)nextY;
    return (sqrt((((double)data->sh.x - nextX) * ((double)data->sh.x - nextX)) + ((double)data->sh.y - nextY) * ((double)data->sh.y - nextY)));
}

void draw_wall_N_S(t_data *data, t_ray ray, int wallX)
{
    int x = 0;
    t_img NO_SO;
        // NO_SO = data->txtr.NO;
    if (ray.angle < M_PI && ray.angle >= 0)
        NO_SO = data->txtr.NO;
    else
        NO_SO = data->txtr.SO;
        // NO_SO = data->txtr.SO;
    int sizeH = (SCREEN_H / ray.dist) * 70;
    sizeH *= 1 / cosf(ray.angle - data->sh.angle);
    if (sizeH > 0)
    {
        // if (sizeH >= 500)
        //     sizeH = 500;
        draw_shape(data, sizeH, wallX, ray.x, NO_SO);
    }
}

void draw_wall_W_E(t_data *data, t_ray ray, int wallX)
{
    int x = 0;
    t_img W_E;
    if((ray.angle >= 0.5* M_PI && ray.angle < 1.5 * M_PI))
        W_E = data->txtr.WE;
        // W_E = data->txtr.WE;
    else
        W_E = data->txtr.EA;
        // W_E = data->txtr.EA;
    int sizeH = (SCREEN_H / ray.dist) * 70;
    sizeH *= 1 / cosf(ray.angle - data->sh.angle);
    if (sizeH > 0)
    {
        // if (sizeH >= 500)
        //     sizeH = 500;
        draw_shape(data, sizeH, wallX, ray.y, W_E);
    }
}

void cast_ray(t_data *data, int wallX, t_ray rayX, t_ray rayY)
{
    t_ray ray;
    int dist = 0;
    int moveX, moveY = 0;
    if (rayX.angle < 0)
        rayX.angle = 2 * M_PI + rayX.angle;
    else if (rayX.angle >= 2 * M_PI)
        rayX.angle = -2 * M_PI + rayX.angle;
    if (rayY.angle < 0)
        rayY.angle = 2 * M_PI + rayY.angle;
    else if (rayY.angle >= 2 * M_PI)
        rayY.angle = -2 * M_PI + rayY.angle;
    if (rayX.angle > M_PI / 2 && rayX.angle < M_PI * 3 / 2)
        moveX = -1;
    else
        moveX = 1;
    if (rayX.angle > 0 && rayX.angle < M_PI)
        moveY = -1;
    else
        moveY = 1;
    // printf(">>%f\n", rayX.angle * 180/M_PI);
    rayX.dist = cast_coll_x(data, moveX, moveY, &rayX);
    rayY.dist = cast_coll_y(data, moveX, moveX, &rayY);
    if (rayX.x <= 0)
        rayX.dist = 2147483647;
    if (rayY.y <= 0)
        rayY.dist = 2147483647;
    if (rayX.dist < rayY.dist)
    {
    // draw_map(data);
        draw_wall_N_S(data, rayX, wallX);
        // draw_line(data, rayX.x, rayX.y, moveX, moveY, 0xFF0000);
    }
    else if (rayX.dist > rayY.dist)
    {
        // draw_line(data, rayY.x, rayY.y, moveX, moveY, 0xFF0000);
        draw_wall_W_E(data, rayY, wallX);
    }
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
    while (i < 3)
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
        wallX -= 3;
        cast_ray(data, wallX, rayX, rayY);
        rayX.angle += 0.25 * M_PI / 180;
        rayY.angle += 0.25 * M_PI / 180;
    }
        // printf("-->%d\n", wallX);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void cast_rays(t_data *data, t_ray rayX, t_ray rayY)
{
    t_ray ray;
    float dist;
    int sizeH = 0;
    int moveX, moveY = 0;
	data->sh.angle = fmod(data->sh.angle , (2 * M_PI));
	if (data->sh.angle < 0)
		data->sh.angle += 2 * M_PI;
    process_game(data, rayX, rayY);
}

void player(t_data *data)
{
    t_ray rayX;
    t_ray rayY;
    cast_rays(data, rayX, rayY);

    // window_grid(data->mlx, data->win, data);
}
void render_walls(t_data *data)
{
    t_ray rayX;
    t_ray rayY;
    draw_background(data, get_color(data->f), get_color(data->c));
    cast_rays(data, rayX, rayY);

}

int ched_ched(int num, t_data *data)
{
    char *pixel;
    int i = 0;
    double newX = 0;
    double newY = 0;
    printf("%d__\n", num);
    if (num == 65307)
        exit(1);
    if (num == 113 && data->map && data->map[(int)(data->sh.y - round(sin(-data->sh.angle + (M_PI / 2))) * 2) / 42][(int)(data->sh.x-round(cos(-data->sh.angle + (M_PI / 2))) * 2) / 42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        data->sh.x -= round(cos(-data->sh.angle - (M_PI / 2))) * 2 * data->sh.mov;
        data->sh.y -= round(sin(-data->sh.angle - (M_PI / 2))) * 2 * data->sh.mov;
        // render_walls(data);
        // draw_map(data);
        // player(data);
    }
    else if (num == 122 && 
        data->map[(int)floor((data->sh.y+round(sin(-data->sh.angle))*2)/42)][(int)floor((data->sh.x+round(cos(-data->sh.angle))*2) / 42)] != '1')
    {
        data->sh.mov = 1;
        // data->sh.x++;
        mlx_clear_window(data->mlx, data->win);
        data->sh.x += round(cos(-data->sh.angle)) * 2 * data->sh.mov;
        data->sh.y += round(sin(-data->sh.angle)) * 2 * data->sh.mov;
        // draw_map(data);
        // player(data); 
        // render_walls(data);
    }
    else if (num == 100 && data->map[(int)(data->sh.y-round(sin(-data->sh.angle - (M_PI / 2)))) / 42][(int)(data->sh.x-round(cos(-data->sh.angle - (M_PI / 2)))) / 42] != '1')
    {
        data->sh.mov = 1;
        mlx_clear_window(data->mlx, data->win);
        data->sh.x -= round(cos(-data->sh.angle + (M_PI / 2))) * 2 * data->sh.mov;
        data->sh.y -= round(sin(-data->sh.angle + (M_PI / 2))) * 2 * data->sh.mov;
        // draw_map(data);
        // player(data); 
        // render_walls(data);
    }
    else if (num == 115 && data->map[(int)(data->sh.y + round(sin(-data->sh.angle + M_PI)) * 2) / 42][(int)(data->sh.x + round(cos(-data->sh.angle + M_PI)) * 2) / 42] != '1')
    {
        // data->sh.mov = -1;
        mlx_clear_window(data->mlx, data->win);
        data->sh.x += round(cos(-data->sh.angle + M_PI)) * 2;
        data->sh.y += round(sin(-data->sh.angle + M_PI)) * 2;
        // draw_map(data);
        // player(data); 
        // render_walls(data);
    }
    else if (num == 65361)
    {
        data->sh.rot = -1;
        data->sh.angle += 5 * (M_PI / 180) * data->sh.rot;
        mlx_clear_window(data->mlx, data->win);
        // draw_map(data);
        // player(data);
        // render_walls(data);
    }
    else if (num == 65363)
    {
        data->sh.rot = 1;
        data->sh.angle += 5 * (M_PI / 180) * data->sh.rot;
        mlx_clear_window(data->mlx, data->win);
        // draw_map(data);
        // player(data);
        // render_walls(data);
    }        
        render_walls(data);
        // draw_map(data);
        // player(data);
        // printf(">>>%f\n", data->sh.angle);
    return 0;
}

int get_color(char *s)
{
    char **clrs = ft_split(s, ',');
    int color = 0;
    int i = 0;
    int c = 0;
    int shifter = 23;
    int p = 2;
    while (i < 3)
    {
        color += ft_atoi(clrs[i]) * pow(256, p);
        p--;
        i++;
    }
    // while (i < 3)
    // {
    //     int num = ft_atoi(clrs[i]);
    //     c = 0;
    //     while (c < 8)
    //     {
    //         if ((num & 1 << c))
    //             color += 1 << shifter;
    //         printf("%d & 1 << %d = %d\n", num, c, (num & 1 << c));
    //         printf("..%d\n", color);
    //         c++;
    //         shifter--;
    //     }
    //     i++;
    // }
    return (color);
}

void draw_background(t_data *data, int floorColor, int ceilColor)
{
    char *pixel;
    int x, y = 0;
    while (y < SCREEN_H / 2)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            pixel = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
            *(int *)pixel = ceilColor;
            x++;
        }
        y++;
    }
    y = SCREEN_H / 2;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            pixel = data->img.addr + (y * data->img.len + x * (data->img.bpp / 8));
            *(int *)pixel = floorColor;
            x++;
        }
        y++;
    }
}

int pressed_key(int num, t_data *data)
{
    if (num == 65307)
        exit(0);
        // free
    if (num == 113)
        data->sh.movX = -1;
    else if (num == 122)
        data->sh.movY = -1;
    else if (num == 100)
        data->sh.movX = 1;
    else if (num == 115)
        data->sh.movY = 1;
    else if (num == 65361)
        data->sh.rot = -1;
    else if (num == 65363)
        data->sh.rot = 1;
    return 0;
}

int release_key(int num, t_data *data)
{
    if (num == 113)
        data->sh.movX = 0;
    else if (num == 122)
        data->sh.movY = 0;
    else if (num == 100)
        data->sh.movX = 0;
    else if (num == 115)
        data->sh.movY = 0;
    else if (num == 65361)
        data->sh.rot = 0;
    else if (num == 65363)
        data->sh.rot = 0;
    return 0;
}

int update(t_data *data)
{
    if (data->i < 2000)
	{
		data->i++;
		return 1;
	}
	else if (data->i == 2000)
		data->i = 0;
    if (data->sh.movX == -1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle - (M_PI / 2))) * 5) / 42][(int)(data->sh.x+round(cos(-data->sh.angle - (M_PI / 2))) * 5) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle - (M_PI / 2))) * 2;
        data->sh.y += round(sin(-data->sh.angle - (M_PI / 2))) * 2;
    }
    if (data->sh.movY == -1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle)) * 5) / 42][(int)(data->sh.x+round(cos(-data->sh.angle)) * 5) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle)) * 2;
        data->sh.y += round(sin(-data->sh.angle)) * 2;
    }
    if (data->sh.movX == 1 && 
    data->map[(int)(data->sh.y - round(sin(-data->sh.angle - (M_PI / 2))) * 5) / 42][(int)(data->sh.x-round(cos(-data->sh.angle - (M_PI / 2))) * 5) / 42] != '1')
    {
        data->sh.x -= round(cos(-data->sh.angle - (M_PI / 2))) * 2;
        data->sh.y -= round(sin(-data->sh.angle - (M_PI / 2))) * 2;   
    }
    if (data->sh.movY == 1 && 
    data->map[(int)(data->sh.y + round(sin(-data->sh.angle + M_PI)) * 5) / 42][(int)(data->sh.x+round(cos(-data->sh.angle + M_PI)) * 5) / 42] != '1')
    {
        data->sh.x += round(cos(-data->sh.angle + M_PI)) * 2;
        data->sh.y += round(sin(-data->sh.angle + M_PI)) * 2; 
    }
    if (data->sh.rot)
        data->sh.angle -= 3 * (M_PI / 180) * data->sh.rot;
    mlx_clear_window(data->mlx, data->win);
    render_walls(data);
    // printf("(%d,%d)->%d,%d(%c)\n", data->sh.x, data->sh.y, data->sh.x/42, data->sh.y/42, data->map[data->sh.y/42][data->sh.x/42]);
    data->i++;
    // usleep(5000);
    return 1;

}
void init_texture(t_data *data)
{
    int x;
    // printf("hahowa sala\n");
    data->txtr.NO.img =  mlx_xpm_file_to_image(data->mlx, data->no, &x, &x);
    data->txtr.NO.addr = mlx_get_data_addr(data->txtr.NO.img, &data->txtr.NO.bpp, &data->txtr.NO.len, &data->txtr.NO.endian);

    data->txtr.SO.img =  mlx_xpm_file_to_image(data->mlx, data->so, &x, &x);
    data->txtr.SO.addr = mlx_get_data_addr(data->txtr.SO.img, &data->txtr.SO.bpp, &data->txtr.SO.len, &data->txtr.SO.endian);

    data->txtr.EA.img =  mlx_xpm_file_to_image(data->mlx, data->ea, &x, &x);
    data->txtr.EA.addr = mlx_get_data_addr(data->txtr.EA.img, &data->txtr.EA.bpp, &data->txtr.EA.len, &data->txtr.EA.endian);

    data->txtr.WE.img =  mlx_xpm_file_to_image(data->mlx, data->we, &x, &x);
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
    data.mlx = mlx_init();
    printf("f--%d\n", get_color(data.f));
    printf("c--%d\n", get_color(data.c));
    // exit(0);
    // printf("f->%x\nc->%x\n",get_color(data.f), get_color(data.c));
    check_text_files(&data);
    data.win = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "kyub_map");
    data.img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
    data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.len, &data.img.endian);
    render_walls(&data);
    // draw_map(&data);
    // player(&data);
    // printf("%s\n", data->no);
    // exit(0);azeaz
    // mlx_do_key_autorepeaton(data->mlx);
    // mlx_hook(data.win, 2, 1L >> 0, ched_ched, &data);
    // mlx_hook(data->win, 2, 1L<<0, ched_ched, data);
    mlx_hook(data.win, 2, 1L<<0, pressed_key, &data);
    mlx_hook(data.win, 3, 1L<<1, release_key, &data);
    mlx_hook(data.win, 17, 1L << 2, &quit, &data);
    mlx_loop_hook(data.mlx, update, &data);
    /*Delete old player position with key release*/
 
    mlx_loop(data.mlx);
}










