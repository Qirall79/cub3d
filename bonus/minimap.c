/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:25:22 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/23 15:50:27 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_square(t_config *config, int x, int y, long int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_UNIT)
	{
		j = 0;
		while (j < MAP_UNIT)
		{
			mlx_put_pixel(config->img, x * MAP_UNIT + j,
				y * MAP_UNIT + i, color);
			j++;
		}
		i++;
	}
}

void	draw_enemy(t_config *config, t_sprite sprite)
{
	float	mini_x;
	float	mini_y;
	int		x;
	int		y;

	mini_x = sprite.x * ((float)MAP_UNIT / UNIT);
	mini_y = sprite.y * ((float)MAP_UNIT / UNIT);
	y = 0;
	while (y < 2)
	{
		x = 0;
		while (x < 2)
		{
			mlx_put_pixel(config->img, mini_x + x, mini_y + y, 0xFFFF00FF);
			mlx_put_pixel(config->img, mini_x - x, mini_y - y, 0xFFFF00FF);
			mlx_put_pixel(config->img, mini_x + x, mini_y - y, 0xFFFF00FF);
			mlx_put_pixel(config->img, mini_x - x, mini_y + y, 0xFFFF00FF);
			x++;
		}
		y++;
	}
}

void	draw_player(t_config *config)
{
	float	mini_x;
	float	mini_y;
	int		x;
	int		y;

	mini_x = config->xPos * ((float)MAP_UNIT / UNIT)
		- config->minimap.start_x * MAP_UNIT;
	mini_y = config->yPos * ((float)MAP_UNIT / UNIT)
		- config->minimap.start_y * MAP_UNIT;
	y = 0;
	while (y < MAP_UNIT / 4)
	{
		x = 0;
		while (x < MAP_UNIT / 4)
		{
			mlx_put_pixel(config->img, mini_x + x, mini_y + y, 0xFF0000FF);
			mlx_put_pixel(config->img, mini_x - x, mini_y + y, 0xFF0000FF);
			mlx_put_pixel(config->img, mini_x + x, mini_y - y, 0xFF0000FF);
			mlx_put_pixel(config->img, mini_x - x, mini_y - y, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

void	draw_miniray(t_config *config)
{
	float	mini_x;
	float	mini_y;
	float	end_x;
	float	end_y;

	mini_x = config->xPos * ((float)MAP_UNIT / UNIT) - 1
		- config->minimap.start_x * MAP_UNIT;
	mini_y = config->yPos * ((float)MAP_UNIT / UNIT) - 1
		- config->minimap.start_y * MAP_UNIT;
	end_x = mini_x + config->dirX * 10;
	end_y = mini_y + config->dirY * 10;
	draw_line(mini_x, mini_y, end_x, end_y, config, 0xFF0F00FF);
}

void	draw_enemies(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->sprite_count)
	{
		if (config->sprites[i].type == ENEMY)
			draw_enemy(config, config->sprites[i]);
		i++;
	}
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
