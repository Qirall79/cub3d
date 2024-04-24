/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/24 12:56:54 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(mlx_key_data_t keydata, t_config *config)
{
	int div;
	int newX;
	int newY;

	div = WIDTH / MAP_WIDTH;
	newX = config->xOffset;
	newY = config->yOffset;
	// if (keydata.action == MLX_RELEASE)
	// 	return ;
	if (keydata.key == MLX_KEY_W)
	{
		newX -= 3;
		if (newX < 0 && config->yOffset)
		{
			if (config->yOffset > 0 && config->map[config->xPos - 1][config->yPos + 1])
				return ;
			else if (config->yOffset < 0 && config->map[config->xPos - 1][config->yPos - 1])
				return ;
		}
		if (!in_range(config->xPos * div + newX, 0, HEIGHT - 1))
			return ;
		if (newX < 0 && abs(newX) >= div
			&& !config->map[config->xPos - 1][config->yPos])
		{
			config->map[config->xPos][config->yPos] = 0;
			config->map[config->xPos - 1][config->yPos] = 5;
			config->xPos--;
			newX = 0;
		}
		else if (newX < 0 && config->map[config->xPos - 1][config->yPos])
			newX += 3;
		config->xOffset = newX;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		newX += 3;
		if (newX > 0 && config->yOffset)
		{
			if (config->yOffset > 0 && config->map[config->xPos + 1][config->yPos + 1])
				return ;
			else if (config->yOffset < 0 && config->map[config->xPos + 1][config->yPos - 1])
				return ;
		}
		if (!in_range(config->xPos * div + newX, 0, HEIGHT - 1))
			return ;
		if (newX > 0 && abs(newX) >= div && !config->map[config->xPos + 1][config->yPos])
		{
			config->map[config->xPos][config->yPos] = 0;
			config->map[config->xPos + 1][config->yPos] = 5;
			config->xPos++;
			newX = 0;
		}
		else if (newX > 0 && config->map[config->xPos + 1][config->yPos])
			newX -= 3;
		config->xOffset = newX;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		newY -= 3;
		if (newY < 0 && config->xOffset)
		{
			if (config->xOffset > 0 && config->map[config->xPos + 1][config->yPos - 1])
				return ;
			else if (config->xOffset < 0 && config->map[config->xPos - 1][config->yPos - 1])
				return ;
		}
		if (!in_range(config->yPos * div + newY, 0, WIDTH - 1))
			return ;
		if (newY < 0 && abs(newY) >= div && !config->map[config->xPos][config->yPos - 1])
		{
			config->map[config->xPos][config->yPos] = 0;
			config->map[config->xPos][config->yPos - 1] = 5;
			config->yPos--;
			newY = 0;
		}
		else if (newY < 0 && config->map[config->xPos][config->yPos - 1])
			newY += 3;
		config->yOffset = newY;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		newY += 3;
		if (newY > 0 && config->xOffset)
		{
			if (config->xOffset > 0 && config->map[config->xPos + 1][config->yPos + 1])
				return ;
			else if (config->xOffset < 0 && config->map[config->xPos - 1][config->yPos + 1])
				return ;
		}
		if (!in_range(config->yPos * div + newY, 0, WIDTH - 1))
			return ;
		if (newY > 0 && abs(newY) >= div && !config->map[config->xPos][config->yPos + 1])
		{
			config->map[config->xPos][config->yPos] = 0;
			config->map[config->xPos][config->yPos + 1] = 5;
			config->yPos++;
			newY = 0;
		}
		else if (newY > 0 && config->map[config->xPos][config->yPos + 1])
			newY -= 3;
		config->yOffset = newY;
	}
	redraw_image(config);
}