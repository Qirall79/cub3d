/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/22 16:04:39 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(mlx_key_data_t keydata, t_config *config)
{
	int div;
	int newX;
	int newY;

	div = WIDTH / MAP_WIDTH;
	newX = config->xPos;
	newY = config->yPos;
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_W)
	{
		newX = config->xPos - 1;
		if (!(newX >= 0 && newX < MAP_HEIGHT && !config->map[newX][newY]))
			return ;
		config->map[config->xPos][config->yPos] = 0;
		config->xPos -= 1;
		config->map[newX][newY] = 5;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		newX = config->xPos + 1;
		if (!(newX >= 0 && newX < MAP_HEIGHT && !config->map[newX][newY]))
			return ;
		config->map[config->xPos][config->yPos] = 0;
		config->xPos = newX;
		config->map[newX][newY] = 5;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		newY = config->yPos - 1;
		if (!(newY >= 0 && newY < MAP_WIDTH && !config->map[newX][newY]))
			return ;
		config->map[config->xPos][config->yPos] = 0;
		config->yPos = newY;
		config->map[newX][newY] = 5;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		newY = config->yPos + 1;
		if (!(newY >= 0 && newY < MAP_WIDTH && !config->map[newX][newY]))
			return ;
		config->map[config->xPos][config->yPos] = 0;
		config->yPos = newY;
		config->map[newX][newY] = 5;
	}
	
	draw_map(config);
}