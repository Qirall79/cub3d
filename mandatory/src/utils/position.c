/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:07:39 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/06 10:52:41 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_pos(t_config *config)
{
	int	i;
	int	j;
	int	sprites_index;

	i = 0;
	sprites_index = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			if (config->map[i][j] == 5)
			{
				config->yPos = i * UNIT + (UNIT - 10) / 2;
				config->xPos = j * UNIT + (UNIT - 10) / 2;
			}
			j++;
		}
		i++;
	}
}

void	copy_map(t_config *config, int map[MAP_HEIGHT][MAP_WIDTH])
{
	int	i;
	int	j;

	i = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			config->map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}
