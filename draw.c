/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/24 13:00:18 by wbelfatm         ###   ########.fr       */
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
}