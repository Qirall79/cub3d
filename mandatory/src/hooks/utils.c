/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:17:06 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:40:55 by wbelfatm         ###   ########.fr       */
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
	if (config->map[y][x] == 1
	|| config->map[y][x] == 4)
		return (1);
	return (0);
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
