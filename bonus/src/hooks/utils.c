/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:17:06 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/15 14:42:47 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	normalize_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return (angle);
}

int	is_wall_v(float newX, float newY, t_config *config)
{
	int	x;
	int	y;

	(void) newX;
	y = (int)(config->y_pos + newY) / UNIT;
	x = (int)(config->x_pos) / UNIT;
	if (y >= config->height || y < 0 || x >= config->width || x < 0)
		return (1);
	if (config->map[y][x] == 1
	|| config->map[y][x] == 4)
		return (1);
	return (0);
}

int	is_wall_h(float newX, float newY, t_config *config)
{
	int	x;
	int	y;

	(void) newY;
	x = (int)(config->x_pos + newX) / UNIT;
	y = (int)(config->y_pos) / UNIT;
	if (y >= config->height || y < 0 || x >= config->width || x < 0)
		return (1);
	if (config->map[y][x] == 1
	|| config->map[y][x] == 4)
		return (1);
	return (0);
}

void	check_collection(t_config *config)
{
	t_vector	map_pos;
	t_vector	collectible_pos;
	int			i;

	map_pos.x = floorf(config->x_pos / UNIT);
	map_pos.y = floorf(config->y_pos / UNIT);
	if (config->map[(int)map_pos.y][(int)map_pos.x] == 3)
	{
		config->map[(int)map_pos.y][(int)map_pos.x] = 0;
		config->collectibles_left--;
		i = -1;
		while (++i < config->sprite_count)
		{
			collectible_pos.x = floorf(config->sprites[i].x / UNIT);
			collectible_pos.y = floorf(config->sprites[i].y / UNIT);
			if (collectible_pos.x == map_pos.x
				&& collectible_pos.y == map_pos.y)
			{
				config->sprites[i].visible = 0;
				break ;
			}
		}
	}
	if (!config->no_collectibles && config->collectibles_left <= 0)
		config->won = 1;
}

void	display_full(t_config *config, int **texture)
{
	int	i;
	int	j;

	i = 0;
	while (i < config->height)
	{
		j = 0;
		while (j < config->width)
		{
			mlx_put_pixel(config->img, j, i, texture[i][j]);
			j++;
		}
		i++;
	}
}
