/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:25:22 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/19 10:28:40 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void draw_enemy(t_config *config)
{
	float mini_x;
	float mini_y;
	int x;
	int y;

	mini_x = config->sprite_pos.x * ((float)MAP_UNIT / UNIT);
	mini_y = config->sprite_pos.y * ((float)MAP_UNIT / UNIT);
	
	y = 0;
	while (y < MAP_UNIT / 4)
	{
		x = 0;
		while (x < MAP_UNIT / 4)
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
	draw_enemy(config);
	draw_miniray(config);
}