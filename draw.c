/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/29 13:12:14 by wbelfatm         ###   ########.fr       */
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
			x = i * div;
			while (x < (i + 1) * div)
			{
				y = j * div;
				while (y < (j + 1) * div)
				{
					if (in_range(x, config->xPos * div + config->xOffset + 5, div * (config->xPos + 1) + config->xOffset - 5)
					&& in_range(y, config->yPos * div + config->yOffset + 5, div * (config->yPos + 1) + config->yOffset - 5))
						mlx_put_pixel(config->img, y, x, 0xFFFF00FF);
					else if (config->map[i][j] && config->map[i][j] != 5)
						mlx_put_pixel(config->img, y, x, 0x0FFFFFFF);
					else
						mlx_put_pixel(config->img, y, x, 0x0);
					y++;
				}
				x++;
			}
			j++;
		}
		i++;
	}
	
	draw_rays(config);
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
		lineEndX = config->initialX + sin(min_angle * M_PI / 180) * WIDTH;
        lineEndY = config->initialY + cos(min_angle * M_PI / 180) * WIDTH;
		draw_line(playerX + config->xOffset, playerY + config->yOffset, lineEndX, lineEndY, config);
		min_angle += config->fovAngle / (double) WIDTH;
	}

}

void draw_line(double yi, double xi, double yf, double xf, t_config *config)
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
		if (((int) round(xi) % MAP_WIDTH == 0 || (int) round(yi) % MAP_WIDTH == 0) && config->map[(int)round(yi / MAP_HEIGHT)][(int)round(xi) / MAP_WIDTH] != 0)
			break ;
        if (xi >= 0 && xi < WIDTH && yi >= 0 && yi < HEIGHT) // Check boundaries before plotting
            mlx_put_pixel(config->img, round(xi), round(yi), 0xFFFFFFFF);
        xi += x_incr;
        yi += y_incr;
    }
}