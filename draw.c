/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/19 10:42:22 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void redraw_image(t_config *config)
{
	mlx_delete_image(config->mlx, config->img);
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		(printf("ERROR initializing MLX image\n"));
	draw_map(config);
}

int in_range(int p, int min, int max)
{
	return (p >= min && p <= max);
}

void draw_map(t_config *config)
{
	// int div;
	// int i;
	// int j;
	// int x;
	// int y;
	// t_vector player;

	// player.x = (config->xPos / UNIT) * SUB_UNIT;
	// player.y = (config->yPos / UNIT) * SUB_UNIT;
	// div = WIDTH / MAP_WIDTH;
	// i = 0;
	// while (i < MAP_HEIGHT)
	// {
	// 	j = 0;
	// 	while (j < MAP_WIDTH)
	// 	{
	// 		y = i * div;
	// 		while (y < (i + 1) * div)
	// 		{
	// 			x = j * div;
	// 			while (x < (j + 1) * div)
	// 			{
						
	// 				if (in_range(x, player.x - 2, player.x + 2)
	// 				&& in_range(y, player.y - 2, player.y + 2))
	// 					mlx_put_pixel(config->img, x, y, 0xFFFF00FF);
	// 				else if (config->map[i][j] == 1)
	// 					mlx_put_pixel(config->img, x, y, 0x0FFFFFFF);
	// 				else
	// 					mlx_put_pixel(config->img, x, y, 0x0);
					
	// 				// draw grids
	// 				if (x % div == 0 || y % div == 0)
	// 					mlx_put_pixel(config->img, x, y, 0xFFFFFFFF);

	// 				x++;
	// 			}
	// 			y++;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	draw_rays(config);
}

void draw_point(t_config *config, int x, int y)
{
	int i = 0;
	int j = 0;

	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(config->img, x + j - 2, y + i - 2, 0xFFFF00FF);
			j++;
		}
		i++;
	}
}

void normalize_vector(t_vector *vec)
{
	float length;

	length = sqrtf(vec->x * vec->x + vec->y * vec->y);
	vec->x = vec->x / length;
	vec->y = vec->y / length;
}

void draw_rays(t_config *config)
{
	t_vector player;

	float min_angle = config->viewAngle - config->fovAngle / 2;
	float max_angle = config->viewAngle + config->fovAngle / 2;

	player.x = (config->xPos / UNIT) * SUB_UNIT;
	player.y = (config->yPos / UNIT) * SUB_UNIT;
	t_vector p;
	float i = 0;
	while (i < WIDTH)
	{
		p = find_intersection(config, normalize_angle(min_angle));
		// p.x = (p.x / UNIT) * SUB_UNIT;
		// p.y = (p.y / UNIT) * SUB_UNIT;
		// draw_line(player.x, player.y, p.x, p.y, config, 0xFF0000FF);
		draw_wall(config, p, min_angle, i);
		min_angle += config->fovAngle / (float) (WIDTH);
		i++;
	}
	
	move_sprite(config);
	draw_sprite(config);
	draw_minimap(config);

}

void draw_line(float xi, float yi, float xf, float yf, t_config *config, int color)
{
    int i;
    float dx;
    float dy;
    float x_incr;
    float y_incr;
    float steps;

    dx = xf - xi;
    dy = yf - yi;
    steps = fabs(dx);
    if (fabs(dx) < fabs(dy))
        steps = fabs(dy);
    i = 0;
    x_incr = (float)dx / steps;
    y_incr = (float)dy / steps;
    while (i++ < steps)
    {
        if (xi >= 0 && xi < WIDTH && yi >= 0 && yi < HEIGHT)
            mlx_put_pixel(config->img, round(xi), round(yi), color);
        xi += x_incr;
        yi += y_incr;
    }
}