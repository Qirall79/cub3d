/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/17 18:05:19 by wbelfatm         ###   ########.fr       */
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

int vertical_facing(float angle)
{
	if (sin(angle * DEG_TO_RAD) > 0.000001f)
		return 1;
	else if (sin(angle * DEG_TO_RAD) < -0.000001f)
		return 2;
	return 0;
}

int horizontal_facing(float angle)
{
	if (cos(angle * DEG_TO_RAD) > 0.000001f)
		return 1;
	else if (cos(angle * DEG_TO_RAD) < -0.000001f)
		return 2;
	return 0;
}

t_vector raycasting_h(t_config *config, float alpha)
{
	alpha = normalize_angle(alpha);
	float aTan = - 1.0f / tan(alpha * DEG_TO_RAD);
	t_vector a;
	t_vector step;

	a.x = config->xPos;
	a.y = config->yPos;
	
	if (vertical_facing(alpha) == BOT)
	{
		// facing down
		a.y = floorf(config->yPos / UNIT) * UNIT + UNIT;
		step.y = UNIT;
		step.x = -step.y * aTan;
	}
	else if (vertical_facing(alpha) == TOP)
	{
		// facing up
		a.y = floorf(config->yPos / UNIT) * UNIT;
		step.y = -UNIT;
		step.x = -step.y * aTan;
	}
	else
		return (a);

	if (step.x > 0 && horizontal_facing(alpha) == LEFT)
		step.x *= -1;
	if (step.x < 0 && horizontal_facing(alpha) == RIGHT)
		step.x *= -1;
		
	a.x = config->xPos + (config->yPos - a.y) * aTan;

	int i = 0;
	int mapX;
	int mapY;
	while (i < MAX_CHECK)
	{
		mapX = (int) a.x / UNIT;
		mapY = (int) (a.y - (vertical_facing(alpha) == TOP ? 1 : 0)) / UNIT;
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
	
	if (horizontal_facing(alpha) == RIGHT)
	{
		// facing right
		a.x = floorf(config->xPos / UNIT) * UNIT + UNIT;
		step.x = UNIT;
		step.y = -step.x * aTan;
	}
	else if (horizontal_facing(alpha) == LEFT)
	{
		// facing left
		a.x = floorf(config->xPos / UNIT) * UNIT;
		step.x = -UNIT;
		step.y = -step.x * aTan;
	}
	else
		return (a);

	if (step.y > 0 && vertical_facing(alpha) == TOP)
		step.y *= -1;
	if (step.y < 0 && vertical_facing(alpha) == BOT)
		step.y *= -1;
	
	a.y = config->yPos + (config->xPos - a.x) * aTan;
	int i = 0;
	int mapX;
	int mapY;
	while (i < MAX_CHECK)
	{
		mapX = (int) (a.x - (horizontal_facing(alpha) == LEFT ? 1 : 0)) / UNIT;
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

	if (p_v.x == config->xPos && p_v.y == config->yPos)
		dist_v = 1e9;
	if (p_h.x == config->xPos && p_h.y == config->yPos)
		dist_h = 1e9;

	p_h.distance = dist_h;
	p_v.distance = dist_v;
	
	if (dist_h <= dist_v)
		return (p_h);
	return (p_v);
}

void draw_wall(t_config *config, t_vector p, float alpha, float x)
{
	float plane_dist = WIDTH / (2 * tan(30 * DEG_TO_RAD));
	float distorted_dist = p.distance;
	float correct_dist = distorted_dist * cos((config->viewAngle - alpha) * DEG_TO_RAD);
	float block_height = UNIT;
	float wall_height = roundf(fabs(block_height / correct_dist) * plane_dist);
	float startY = (HEIGHT / 2) - (wall_height / 2);
	float endY = startY + wall_height;
	
	if (endY >= HEIGHT)
		endY = HEIGHT - 1;

	float y;
	int texture_x;
	int texture_y;
	int color;
	if (p.z)
		texture_x = ((int)p.y % TEX_WIDTH);
	else
		texture_x = ((int)p.x % TEX_WIDTH);
	

	// draw ceiling
	y = 0;
	while (y < startY)
	{
		mlx_put_pixel(config->img, x, y, 0x0F00FF4F);
		y++;
	}

	// draw wall
	y = startY;
	while (y < endY && y < HEIGHT)
	{
		texture_y = (int)((y - startY) * ((float) TEX_HEIGHT / wall_height));

		// direction
		if (p.z && horizontal_facing(alpha) == LEFT)
			color = config->texture_east[texture_y][texture_x];
		else if (p.z && horizontal_facing(alpha) == RIGHT)
			color = config->texture_west[texture_y][texture_x];
		else if (!p.z && vertical_facing(alpha) == TOP)
			color = config->texture_north[texture_y][texture_x];
		else if (!p.z && vertical_facing(alpha) == BOT)
			color = config->texture_south[texture_y][texture_x];

		if (y < 0)
			y = 0;
		if (!in_range(x, 0, WIDTH - 1) || !in_range(y, 0, HEIGHT - 1))
			mlx_put_pixel(config->img, x, 0, color);
		else
			mlx_put_pixel(config->img, x, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		mlx_put_pixel(config->img, x, y, 0xFF0F000F);
		y++;
	}
}

void draw_sprite(t_config *config)
{
	int y = 0;
	int x = 0;
	t_vector diff;

	diff.x = (config->sprite_pos.x - config->xPos);
	diff.y = (config->sprite_pos.y - config->yPos);

	float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
	printf("%f\n", distance);
	float diff_angle = normalize_angle(config->viewAngle - atan2(diff.y, diff.x) * (1.0 / DEG_TO_RAD));

	float screen_angle = (config->fovAngle / 2.0) - diff_angle;
	float fov_ratio = WIDTH / config->fovAngle;
	float plane_dist = WIDTH / (2.0 * tan(30 * DEG_TO_RAD));

	float sprite_height = ((float)UNIT / distance) * plane_dist;
	int startY = (HEIGHT / 2) - (sprite_height / 2);
	if (startY < 0)
		startY = 0;
	int endY = startY + sprite_height;

	if (endY >= HEIGHT)
		endY = HEIGHT - 1;

	float sprite_angle = normalize_angle(-diff_angle);
	float sprite_width = sprite_height;
	float columnX = tan(sprite_angle * DEG_TO_RAD) * plane_dist;
	float startX = (WIDTH / 2) + columnX - sprite_width / 2;
	float endX = startX + sprite_width;
	int texture_x;
	int texture_y;

	if (diff_angle > 180)
		diff_angle = 360 - diff_angle;
	
	y = startY;
	if (diff_angle < (config->fovAngle / 2) + 10)
	{
		while (y < endY && y < HEIGHT)
		{
			x = startX;
			if (x < 0)
				x = 0;
			while (x >= 0 && x < endX && x < WIDTH)
			{
				texture_y = (int)((y - startY) * ((float) UNIT / sprite_height));
				texture_x = (int)((x - startX) * ((float) UNIT / sprite_width));
				if (in_range(texture_x, 0, UNIT - 1) && in_range(texture_y, 0, UNIT - 1)
				&& (char)config->sprite[texture_y][texture_x] != 0)
					mlx_put_pixel(config->img, x, y, config->sprite[texture_y][texture_x]);
				x++;
			}
			y++;
		}
	}
}

void fill_square(t_config *config, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < MAP_UNIT)
	{
		j = 0;
		while (j < MAP_UNIT)
		{
			mlx_put_pixel(config->img, x * MAP_UNIT + j, y * MAP_UNIT + i, color);
			j++;
		}
		i++;
	}
}

void draw_player(t_config *config)
{
	float mini_x;
	float mini_y;
	int x;
	int y;

	mini_x = config->xPos * ((float)MAP_UNIT / UNIT);
	mini_y = config->yPos * ((float)MAP_UNIT / UNIT);
	
	y = 0;
	while (y < MAP_UNIT / 4)
	{
		x = 0;
		while (x < MAP_UNIT / 4)
		{
			mlx_put_pixel(config->img, mini_x + x, mini_y + y, 0xFF0000FF);
			mlx_put_pixel(config->img, mini_x - x, mini_y - y, 0xFF0000FF);
			mlx_put_pixel(config->img, mini_x + x, mini_y - y, 0xFF0000FF);
			mlx_put_pixel(config->img, mini_x - x, mini_y + y, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

void draw_miniray(t_config *config)
{
	float mini_x;
	float mini_y;
	float end_x;
	float end_y;

	mini_x = config->xPos * ((float)MAP_UNIT / UNIT) - MAP_UNIT / 8;
	mini_y = config->yPos * ((float)MAP_UNIT / UNIT) - MAP_UNIT / 8;
	end_x = mini_x + config->dirX * 10;
	end_y = mini_y + config->dirY * 10;
	
	draw_line(mini_x, mini_y, end_x, end_y, config, 0xFF0F00FF);
}

void draw_minimap(t_config *config)
{
	int x;
	int y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (config->map[y][x] == 1)
				fill_square(config, x, y, 0xFFFFFFAF);
			else
				fill_square(config, x, y, 0x0);
			x++;
		}
		y++;
	}
	draw_player(config);
	draw_miniray(config);
}

void draw_rays(t_config *config)
{
	float playerX = config->xPos;
	float playerY = config->yPos;
	float min_angle = config->viewAngle - config->fovAngle / 2;
	float max_angle = config->viewAngle + config->fovAngle / 2;

	t_vector p;
	float i = 0;
	while (i < WIDTH)
	{
		p = find_intersection(config, min_angle);
		// draw_line(playerX, playerY, p.x, p.y, config, 0xFF0000FF);
		draw_wall(config, p, min_angle, i);
		min_angle += config->fovAngle / (float) (WIDTH);
		i++;
	}
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