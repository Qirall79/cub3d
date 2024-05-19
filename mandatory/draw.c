/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/19 21:27:42 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void redraw_image(t_config *config)
{
	mlx_delete_image(config->mlx, config->img);
	config->img = mlx_new_image(config->mlx, config->width, config->height);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		(printf("ERROR initializing MLX image\n"));
	draw_three_d(config);
}

int in_range(int p, int min, int max)
{
	return (p >= min && p <= max);
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
	float min_angle;
	float i;
	t_vector p;

	i = 0;
	player.x = (config->xPos / UNIT) * SUB_UNIT;
	player.y = (config->yPos / UNIT) * SUB_UNIT;
	min_angle = config->viewAngle - config->fovAngle / 2;
	while (i < config->width)
	{
		p = find_intersection(config, normalize_angle(min_angle));
		p.x = (p.x / UNIT) * SUB_UNIT;
		p.y = (p.y / UNIT) * SUB_UNIT;
		draw_line(player.x, player.y, p.x, p.y, config, 0xFF0000FF);
		min_angle += config->fovAngle / (float) (config->width);
		i++;
	}
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
        if (xi >= 0 && xi < config->width && yi >= 0 && yi < config->height)
            mlx_put_pixel(config->img, round(xi), round(yi), color);
        xi += x_incr;
        yi += y_incr;
    }
}

void draw_three_d(t_config *config)
{
	float min_angle;
	float i;
	t_vector p;

	i = 0;
	min_angle = config->viewAngle - config->fovAngle / 2;
	while (i < config->width)
	{
		p = find_intersection(config, normalize_angle(min_angle));
		draw_wall(config, p, min_angle, i);
		min_angle += config->fovAngle / (float) (config->width);
		i++;
	}
}