/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/01 19:43:37 by wbelfatm         ###   ########.fr       */
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
					if (in_range(x, config->xPos * div + config->xOffset + 5, div * (config->xPos + 1) + config->xOffset - 5)
					&& in_range(y, config->yPos * div + config->yOffset + 5, div * (config->yPos + 1) + config->yOffset - 5))
						mlx_put_pixel(config->img, x, y, 0xFFFF00FF);
					else if (config->map[i][j] && config->map[i][j] != 5)
						mlx_put_pixel(config->img, x, y, 0x0FFFFFFF);
					else
						mlx_put_pixel(config->img, x, y, 0x0);
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

void collision_x(t_config *config, float alpha, int *lineEndX, int *lineEndY)
{
	int unit = WIDTH / MAP_WIDTH;
	float direction = sin(config->viewAngle * M_PI / 180);
	int a_x;
	int a_y;
	float x_incr;
	float y_incr;
	int playerX = config->xPos * unit + unit / 2;
	int playerY = config->yPos * unit + unit / 2;

	x_incr = unit / tan(alpha * M_PI / 180);
	if (direction < 0)
	{
		a_y = floorf(playerY / unit) * unit - 1;
		y_incr = -unit;
	}
	else {
		a_y = floorf(playerY / unit) * unit + unit;
		y_incr = unit;
	}
	a_x = playerX + (playerY - a_y) / tan(alpha * M_PI / 180);
	while (in_range((int)(a_y / unit), 0, MAP_HEIGHT) && in_range((int)a_x / unit, 0, MAP_WIDTH)
		&& !config->map[(int)(a_y / unit)][(int)a_x / unit])
	{
		a_y += y_incr;
		a_x += x_incr;
	}
	
	*lineEndX = a_x;
	*lineEndY = a_y;
}

void collision_y(t_config *config, float alpha, int *lineEndX, int *lineEndY)
{
	int unit = WIDTH / MAP_WIDTH;
	float direction = cos(config->viewAngle * M_PI / 180);
	int a_x;
	int a_y;
	float x_incr;
	float y_incr;
	int playerX = config->xPos * unit + unit / 2;
	int playerY = config->yPos * unit + unit / 2;

	y_incr = unit * tan(alpha * M_PI / 180);
	if (direction < 0)
	{
		a_x = floorf(playerX / unit) * unit - 1;
		x_incr = -unit;
	}
	else {
		a_x = floorf(playerX / unit) * unit + unit;
		x_incr = unit;
	}
	a_y = playerY + (playerX - a_x) * tan(alpha * M_PI / 180);

	while (in_range((int)(a_y / unit), 0, MAP_HEIGHT) && in_range((int)a_x / unit, 0, MAP_WIDTH)
		&& !config->map[(int)(a_y / unit)][(int)a_x / unit])
	{
		a_y += y_incr;
		a_x += x_incr;
	}
	
	if (a_x <= *lineEndX && a_y <= *lineEndY)
	{
		*lineEndX = a_x;
		*lineEndY = a_y;
	}
}

void draw_rays(t_config *config)
{
	int div = HEIGHT / MAP_HEIGHT;
	int playerX = config->xPos * div + div / 2;
	int playerY = config->yPos * div + div / 2;
	int lineEndX = config->dirX;
	int lineEndY = config->dirY;
	double min_angle = config->viewAngle - config->fovAngle / 2;
	double max_angle = config->viewAngle + config->fovAngle / 2;
	
	
	while (min_angle <= max_angle)
	{
		collision_x(config, min_angle, &lineEndX, &lineEndY);
		collision_y(config, min_angle, &lineEndX, &lineEndY);
		draw_line(playerX + config->xOffset, playerY + config->yOffset, lineEndX, lineEndY, config);
		min_angle += config->fovAngle / (double) WIDTH;
	}

}

void draw_line(double xi, double yi, double xf, double yf, t_config *config)
{
    int i;
    double dx;
    double dy;
    double x_incr;
    double y_incr;
    int steps;
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
            mlx_put_pixel(config->img, round(xi), round(yi), 0xFF0000FF);
        xi += x_incr;
        yi += y_incr;
    }
}