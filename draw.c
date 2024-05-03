/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/03 14:45:06 by wbelfatm         ###   ########.fr       */
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

void draw_point(t_config *config, int x, int y)
{
	int i = 0;
	int j = 0;

	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(config->img, x + j - 2, y + i - 2, 0xFF00FFFF);
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

t_vector dda_casting(t_config *config, float alpha)
{
	int unit = WIDTH / MAP_WIDTH;
	t_vector player = {config->xPos * unit + unit / 2 + config->xOffset, config->yPos * unit + unit / 2 + config->yOffset};
	t_vector rayDir = {cos(alpha * M_PI / 180), sin(alpha * M_PI / 180)};
	t_vector step;
	t_vector rayLength;
	t_vector rayUnitStep;
	t_vector mapCheck = player;

	normalize_vector(&rayDir);

	rayUnitStep.x = sqrtf(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x));
	rayUnitStep.y = sqrtf(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y));
	
	if (rayDir.x < 0)
	{
		step.x = -1;
		rayLength.x = (player.x - mapCheck.x) * rayUnitStep.x;
	}
	else
	{
		step.x = 1;
		rayLength.x = (mapCheck.x + 1 - player.x) * rayUnitStep.x;
	}
	
	if (rayDir.y < 0)
	{
		step.y = -1;
		rayLength.y = (player.y - mapCheck.y) * rayUnitStep.y;
	}
	else
	{
		step.y = 1;
		rayLength.y = (mapCheck.y + 1 - player.y) * rayUnitStep.y;
	}

	int wallFound = 0;
	float distance;
	distance = 0;

	while (!wallFound && distance < WIDTH)
	{
		if (rayLength.x < rayLength.y)
		{
			mapCheck.x += step.x;
			distance = rayLength.x;
			rayLength.x += rayUnitStep.x;
		}
		else {
			mapCheck.y += step.y;
			distance = rayLength.y;
			rayLength.y += rayUnitStep.y;
		}
		
		if (in_range(mapCheck.x, 0, WIDTH) && in_range(mapCheck.y, 0, HEIGHT))
		{
			if (config->map[(int)mapCheck.y / unit][(int)mapCheck.x / unit] && config->map[(int)mapCheck.y / unit][(int)mapCheck.x / unit] != 5)
				wallFound = 1;
		}
		else
		{
			break ;
		}
	}
	
	t_vector p = {player.x + rayDir.x * distance, player.y + rayDir.y * distance};
	return p;
}

void draw_rays(t_config *config)
{
	int div = HEIGHT / MAP_HEIGHT;
	int playerX = config->xPos * div + div / 2;
	int playerY = config->yPos * div + div / 2;
	int lineEndX = config->dirX + config->initialX;
	int lineEndY = config->dirY + config->initialY;
	double min_angle = config->viewAngle - config->fovAngle / 2;
	double max_angle = config->viewAngle + config->fovAngle / 2;

	t_vector p;

	while (min_angle <= max_angle)
	{
		p = dda_casting(config, min_angle);
		draw_line(playerX + config->xOffset, playerY + config->yOffset, p.x, p.y, config);
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