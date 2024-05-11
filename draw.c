/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/11 10:46:25 by wbelfatm         ###   ########.fr       */
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
						
					// if (in_range(x, config->player.x - 5, config->player.x + 5)
					// && in_range(y, config->player.y - 5, config->player.y + 5))
					// 	mlx_put_pixel(config->img, x, y, 0xFFFF00FF);
					// else if (config->map[i][j] == 1)
					// 	mlx_put_pixel(config->img, x, y, 0x0FFFFFFF);
					// else
					// 	mlx_put_pixel(config->img, x, y, 0x0);
					
					// // // // draw grids
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
			mlx_put_pixel(config->img, x + j, y + i, 0xFFFF00FF);
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

	a.x = config->player.x;
	a.y = config->player.y;
	
	if (sin(alpha * DEG_TO_RAD) > 0.001f)
	{
		// facing down
		a.y = floorf(config->player.y / UNIT) * UNIT + UNIT;
		step.y = UNIT;
		step.x = -step.y * aTan;
	}
	else if (sin(alpha * DEG_TO_RAD) < -0.001f)
	{
		// facing up
		a.y = floorf(config->player.y / UNIT) * UNIT - 0.001f;
		step.y = -UNIT;
		step.x = -step.y * aTan;
	}
	else
		return (a);
	a.x = config->player.x + (config->player.y - a.y) * aTan;
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

	a.x = config->player.x;
	a.y = config->player.y;
	
	if (cos(alpha * DEG_TO_RAD) > 0.001f)
	{
		// facing right
		a.x = floorf(config->player.x / UNIT) * UNIT + UNIT;
		step.x = UNIT;
		step.y = -step.x * aTan;
	}
	else if (cos(alpha * DEG_TO_RAD) < -0.001f)
	{
		// facing left
		a.x = floorf(config->player.x / UNIT) * UNIT - 0.001f;
		step.x = -UNIT;
		step.y = -step.x * aTan;
	}
	else
		return (a);
	a.y = config->player.y + (config->player.x - a.x) * aTan;
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

	dist_h = sqrtf((config->player.x - p_h.x) * (config->player.x - p_h.x) + (config->player.y - p_h.y) * (config->player.y - p_h.y));
	dist_v = sqrtf((config->player.x - p_v.x) * (config->player.x - p_v.x) + (config->player.y - p_v.y) * (config->player.y - p_v.y));
	
	if (p_v.x == config->player.x)
		return (p_h);
	if (p_h.x == config->player.x)
		return (p_v);
	if (dist_h <= dist_v)
		return (p_h);
	return (p_v);
}

void draw_wall(t_config *config, t_vector p, float alpha, float x)
{
	float plane_dist = WIDTH / (2 * tan(30 * DEG_TO_RAD));
	float distorted_dist = sqrtf((config->player.x - p.x) * (config->player.x - p.x) + (config->player.y - p.y) * (config->player.y - p.y));
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

t_vector my_raycaster(t_config *config, float alpha, int x)
{
	t_vector pos = {config->player.x, config->player.y};
	float cameraX;
	t_vector rayDir;
	t_vector map;
	t_vector sideDist;
	t_vector deltaDist;
	t_vector step;
	t_vector perpWallDist;
	int wallFound = 0;
	int side;

	cameraX = 2 * x / (float)WIDTH - 1;
	
	rayDir.x = config->dir.x + config->plane.x * cameraX;
	rayDir.y = config->dir.y + config->plane.y * cameraX;

	map.x = (int) pos.x;
	map.y = (int) pos.y;

	if (rayDir.x < 0.000001 && rayDir.x > -0.000001)
		deltaDist.x = 1e30;
	else
		deltaDist.x = fabs(1 / rayDir.x);
	
	if (rayDir.y < 0.000001 && rayDir.y > -0.000001)
		deltaDist.y = 1e30;
	else
		deltaDist.y = fabs(1 / rayDir.y);
	
	// deltaDist.x = sqrtf(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x));
	// deltaDist.y = sqrtf(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y));

	if (rayDir.x < 0)
	{
		step.x = -1;
		sideDist.x = (pos.x - map.x) * deltaDist.x;
	}
	else
	{
		step.x = 1;
		sideDist.x = (map.x + 1.0 - pos.x) * deltaDist.x;
	}
	
	if (rayDir.y < 0)
	{
		step.y = -1;
		sideDist.y = (pos.y - map.y) * deltaDist.y;
	}
	else
	{
		step.y = 1;
		sideDist.y = (map.y + 1.0 - pos.y) * deltaDist.y;
	}

	while (!wallFound)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			map.y += step.y;
			side = 1;
		}
		if (is_wall(config->map[(int)map.y][(int)map.x]))
			wallFound = 1;
	}
	if (side == 0)
		perpWallDist.x = (sideDist.x - deltaDist.x);
	else
		perpWallDist.x = (sideDist.y - deltaDist.y);
	
	if (perpWallDist.x < 0.000001 && perpWallDist.x > -0.000001)
		perpWallDist.x = 1;
	perpWallDist.z = side;
	perpWallDist.y = config->map[(int)map.y][(int)map.x];
	return perpWallDist;
}

void build_wall(t_config *config, int x, float distance, int side, int wall)
{
	int line_height = (int) (HEIGHT / distance);
	int start = -line_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	int end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;

	if (wall == 1)
	{
		if (side == 0)
			draw_line(x, start, x, end, config, 0xFFFFFFFF);
		else
			draw_line(x, start, x, end, config, 0xFFFFFFAF);
	}
	if (wall == 2)
	{
		if (side == 0)
			draw_line(x, start, x, end, config, 0xFFFF00FF);
		else
			draw_line(x, start, x, end, config, 0xFFFF00AF);
	}
	if (wall == 3)
	{
		if (side == 0)
			draw_line(x, start, x, end, config, 0xFF00FFFF);
		else
			draw_line(x, start, x, end, config, 0xFF00FFAF);
	}
	if (wall == 4)
	{
		if (side == 0)
			draw_line(x, start, x, end, config, 0x00FFFFFF);
		else
			draw_line(x, start, x, end, config, 0x00FFFFAF);
	}

}

void draw_rays(t_config *config)
{
	float playerX = config->player.x;
	float playerY = config->player.y;
	float min_angle = config->viewAngle - config->fovAngle / 2;
	float max_angle = config->viewAngle + config->fovAngle / 2;

	t_vector p;
	float distance;
	float i = 0;
	while (i < WIDTH)
	{
		p = my_raycaster(config, min_angle, i);
		build_wall(config, i, p.x, p.z, p.y);
		// draw_line(playerX, playerY, p.x, p.y, config, 0xFF0000FF);
		// draw_wall(config, p, min_angle, i++);
		min_angle += config->fovAngle / (float) (WIDTH);
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