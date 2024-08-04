/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:25:22 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 23:01:36 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_miniray(t_config *config)
{
	t_vector	start;
	t_vector	end;

	start.x = config->xPos * ((float)MAP_UNIT / UNIT) - 1
		- config->minimap.start_x * MAP_UNIT;
	start.y = config->yPos * ((float)MAP_UNIT / UNIT) - 1
		- config->minimap.start_y * MAP_UNIT;
	end.x = start.x + config->dirX * 10;
	end.y = start.y + config->dirY * 10;
	draw_line(start, end, config, 0xFF0F00FF);
}

void	set_minimap_params(t_config *config, t_vector start, t_vector end)
{
	config->minimap = (t_minimap){
		.start_x = (int)start.x,
		.start_y = (int)start.y,
		.end_x = (int)end.x,
		.end_y = (int)end.y,
	};
}

void	init_minimap(t_config *config)
{
	t_vector	start;
	t_vector	end;

	start.x = (int)floorf(config->xPos / UNIT) - 6;
	if (start.x < 0)
		start.x = 0;
	start.y = (int)floorf(config->yPos / UNIT) - 6;
	if (start.y < 0)
		start.y = 0;
	end.x = start.x + 13;
	if (end.x >= config->map_width)
	{
		end.x = config->map_width - 1;
		start.x = end.x - 13;
	}
	end.y = start.y + 13;
	if (end.y >= config->map_height)
	{
		end.y = config->map_height - 1;
		start.y = end.y - 13;
	}
	set_minimap_params(config, start, end);
}

void	draw_minimap(t_config *config)
{
	int	x;
	int	y;

	init_minimap(config);
	y = config->minimap.start_y;
	while (y <= config->minimap.end_y)
	{
		x = config->minimap.start_x;
		while (x <= config->minimap.end_x)
		{
			if (config->map[y][x] == 1)
				fill_square(config, x - config->minimap.start_x,
					y - config->minimap.start_y, 0xFFFFFFAF);
			else if (config->map[y][x] == 4)
				fill_square(config, x - config->minimap.start_x,
					y - config->minimap.start_y, 0xFFFF00FFF);
			else
				fill_square(config, x - config->minimap.start_x,
					y - config->minimap.start_y, 0x0);
			x++;
		}
		y++;
	}
	draw_player(config);
	draw_miniray(config);
}
