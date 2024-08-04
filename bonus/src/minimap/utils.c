/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:54:38 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 23:01:48 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
