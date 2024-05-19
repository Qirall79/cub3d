/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 21:24:25 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/19 21:25:08 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_two_d(t_config *config)
{
	int div;
	int i;
	int j;
	int x;
	int y;
	t_vector player;

	player.x = (config->xPos / UNIT) * SUB_UNIT;
	player.y = (config->yPos / UNIT) * SUB_UNIT;
	div = config->width / MAP_WIDTH;
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
						
					if (in_range(x, player.x - 2, player.x + 2)
					&& in_range(y, player.y - 2, player.y + 2))
						mlx_put_pixel(config->img, x, y, 0xFFFF00FF);
					else if (config->map[i][j] == 1)
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