/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/09 20:41:00 by wbelfatm         ###   ########.fr       */
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
	int div;
	int i;
	int j;
	int x;
	int y;

	div = WIDTH / MAP_WIDTH;
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			y = i * div;
			while (y < (i + 1) * div)
			{
				x = j * div;
				while (x < (j + 1) * div)
				{
						
					// if (in_range(x, config->xPos - 5, config->xPos + 5)
					// && in_range(y, config->yPos - 5, config->yPos + 5))
					// 	mlx_put_pixel(config->img, x, y, 0xFFFF00FF);
					// else if (config->map[i][j] == 1)
					// 	mlx_put_pixel(config->img, x, y, 0x0FFFFFFF);
					// else
					// 	mlx_put_pixel(config->img, x, y, 0x0);
					
					// // // draw grids
					// if (x % UNIT == 0 || y % UNIT == 0)
					// 	mlx_put_pixel(config->img, x, y, 0xFFFFFFFF);

					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
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



t_vector raycasting_h(t_config *config, float alpha)
{
	alpha = normalize_angle(alpha);
	float aTan = - 1.0f / tan(alpha * DEG_TO_RAD);
	t_vector a;
	t_vector step;

	a.x = config->xPos;
	a.y = config->yPos;
	
	if (sin(alpha * DEG_TO_RAD) > 0.001f)
	{
		// facing down
		a.y = floorf(config->yPos / UNIT) * UNIT + UNIT;
		step.y = UNIT;
		step.x = -step.y * aTan;
	}
	else if (sin(alpha * DEG_TO_RAD) < -0.001f)
	{
		// facing up
		a.y = floorf(config->yPos / UNIT) * UNIT - 0.001f;
		step.y = -UNIT;
		step.x = -step.y * aTan;
	}
	else
		return (a);
	a.x = config->xPos + (config->yPos - a.y) * aTan;
	int i = 0;
	int mapX;
	int mapY;
	while (i < MAX_CHECK)
	{
		mapX = (int) a.x / UNIT;
		mapY = (int) a.y / UNIT;
		if (in_range(mapX, 0, MAP_WIDTH - 1) && in_range(mapY, 0, MAP_HEIGHT - 1) && config->map[mapY][mapX] == 1)
			break ;
		a.x += step.x;
		a.y += step.y;
		i++;
	}
	return a;
}

t_vector raycasting_v(t_config *config, float alpha)
{
	alpha = normalize_angle(alpha);
	float aTan = -tan(alpha * DEG_TO_RAD);
	t_vector a;
	t_vector step;

	a.x = config->xPos;
	a.y = config->yPos;
	
	if (cos(alpha * DEG_TO_RAD) > 0.001f)
	{
		// facing right
		a.x = floorf(config->xPos / UNIT) * UNIT + UNIT;
		step.x = UNIT;
		step.y = -step.x * aTan;
	}
	else if (cos(alpha * DEG_TO_RAD) < -0.001f)
	{
		// facing left
		a.x = floorf(config->xPos / UNIT) * UNIT - 0.001f;
		step.x = -UNIT;
		step.y = -step.x * aTan;
	}
	else
		return (a);
	a.y = config->yPos + (config->xPos - a.x) * aTan;
	int i = 0;
	int mapX;
	int mapY;
	while (i < MAX_CHECK)
	{
		mapX = (int) a.x / UNIT;
		mapY = (int) a.y / UNIT;
		if (in_range(mapX, 0, MAP_WIDTH - 1) && in_range(mapY, 0, MAP_HEIGHT - 1) && config->map[mapY][mapX] == 1)
			break ;
		a.x += step.x;
		a.y += step.y;
		i++;
	}
	return a;
}

t_vector find_intersection(t_config *config, float alpha)
{
	t_vector p_h;
	t_vector p_v;
	float dist_h;
	float dist_v;

	p_h = raycasting_h(config, alpha);
	p_v = raycasting_v(config, alpha);
	p_v.z = 1;
	p_h.z = 0;

	dist_h = sqrtf((config->xPos - p_h.x) * (config->xPos - p_h.x) + (config->yPos - p_h.y) * (config->yPos - p_h.y));
	dist_v = sqrtf((config->xPos - p_v.x) * (config->xPos - p_v.x) + (config->yPos - p_v.y) * (config->yPos - p_v.y));
	
	if (p_v.x == config->xPos)
		return (p_h);
	if (p_h.x == config->xPos)
		return (p_v);
	if (dist_h <= dist_v)
		return (p_h);
	return (p_v);
}

void draw_wall(t_config *config, t_vector p, float alpha, float x)
{
	float plane_dist = WIDTH / (2 * tan(30 * DEG_TO_RAD));
	float distorted_dist = sqrtf((config->xPos - p.x) * (config->xPos - p.x) + (config->yPos - p.y) * (config->yPos - p.y));
	float correct_dist = distorted_dist * cos((config->viewAngle - alpha) * DEG_TO_RAD);
	float block_height = WIDTH / MAP_WIDTH;
	float wall_height = roundf(fabs((block_height / correct_dist) * plane_dist));
	float startY = (HEIGHT / 2) - (wall_height / 2);
	float endY = startY + wall_height;
	
	if (p.z)
		draw_line(x, startY, x, endY, config, 0x00F0FFAF);
	else
		draw_line(x, startY, x, endY, config, 0x00F0FFFF);
}


void draw_rays(t_config *config)
{
	float playerX = config->xPos;
	float playerY = config->yPos;
	float min_angle = config->viewAngle - config->fovAngle / 2;
	float max_angle = config->viewAngle + config->fovAngle / 2;

	t_vector p;
	float i = 0;
	while (min_angle <= max_angle)
	{
		p = find_intersection(config, min_angle);
		// draw_line(playerX, playerY, p.x, p.y, config, 0xFF0000FF);
		draw_wall(config, p, min_angle, i++);
		min_angle += config->fovAngle / (float) (WIDTH);
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
	// int div = WIDTH / MAP_WIDTH;

    dx = xf - xi;
    dy = yf - yi;
    steps = fabs(dx);
    if (fabs(dx) < fabs(dy))
        steps = fabs(dy);
    i = 0;
    x_incr = (float)dx / steps; // Use floating-point division
    y_incr = (float)dy / steps; // Use floating-point division
    while (i++ < steps)
    {
        if (xi >= 0 && xi < WIDTH && yi >= 0 && yi < HEIGHT) // Check boundaries before plotting
            mlx_put_pixel(config->img, round(xi), round(yi), color);
        xi += x_incr;
        yi += y_incr;
    }
}