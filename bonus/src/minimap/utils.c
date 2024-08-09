/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:54:38 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:08:17 by wbelfatm         ###   ########.fr       */
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

void	draw_player(t_config *config)
{
	float	mini_x;
	float	mini_y;
	int		x;
	int		y;

	mini_x = config->x_pos * ((float)MAP_UNIT / UNIT)
		- config->minimap.start_x * MAP_UNIT;
	mini_y = config->y_pos * ((float)MAP_UNIT / UNIT)
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
