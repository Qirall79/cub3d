/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/01 18:42:21 by wbelfatm         ###   ########.fr       */
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
	if (keydata.key == MLX_KEY_A)
	{
		newX -= 3;
		if (newX < 0 && config->yOffset)
		{
			if (config->yOffset > 0 && config->map[config->yPos + 1][config->xPos - 1])
				return ;
			else if (config->yOffset < 0 && config->map[config->yPos - 1][config->xPos - 1])
				return ;
		}
		if (!in_range(config->xPos * div + newX, 0, WIDTH - 1))
			return ;
		if (newX < 0 && abs(newX) >= div
			&& !config->map[config->yPos][config->xPos - 1])
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[config->yPos][config->xPos - 1] = 5;
			config->xPos--;
			newX = 0;
		}
		else if (newX < 0 && config->map[config->yPos][config->xPos - 1])
			newX += 3;
		config->xOffset = newX;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		newX += 3;
		if (newX > 0 && config->yOffset)
		{
			if (config->yOffset > 0 && config->map[config->yPos + 1][config->xPos + 1])
				return ;
			else if (config->yOffset < 0 && config->map[config->yPos - 1][config->xPos + 1])
				return ;
		}
		if (!in_range(config->xPos * div + newX, 0, HEIGHT - 1))
			return ;
		if (newX > 0 && abs(newX) >= div && !config->map[config->yPos][config->xPos + 1])
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[config->yPos][config->xPos + 1] = 5;
			config->xPos++;
			newX = 0;
		}
		else if (newX > 0 && config->map[config->yPos][config->xPos + 1])
			newX -= 3;
		config->xOffset = newX;
	}
	else if (keydata.key == MLX_KEY_W)
	{
		newY -= 3;
		if (newY < 0 && config->xOffset)
		{
			if (config->xOffset > 0 && config->map[config->yPos - 1][config->xPos + 1])
				return ;
			else if (config->xOffset < 0 && config->map[config->yPos - 1][config->xPos - 1])
				return ;
		}
		if (!in_range(config->yPos * div + newY, 0, WIDTH - 1))
			return ;
		if (newY < 0 && abs(newY) >= div && !config->map[config->yPos - 1][config->xPos])
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[config->yPos - 1][config->xPos] = 5;
			config->yPos--;
			newY = 0;
		}
		else if (newY < 0 && config->map[config->yPos - 1][config->xPos])
			newY += 3;
		config->yOffset = newY;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		newY += 3;
		if (newY > 0 && config->xOffset)
		{
			if (config->xOffset > 0 && config->map[config->yPos + 1][config->xPos + 1])
				return ;
			else if (config->xOffset < 0 && config->map[config->yPos + 1][config->xPos - 1])
				return ;
		}
		if (!in_range(config->yPos * div + newY, 0, WIDTH - 1))
			return ;
		if (newY > 0 && abs(newY) >= div && !config->map[config->yPos + 1][config->xPos])
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[config->yPos + 1][config->xPos] = 5;
			config->yPos++;
			newY = 0;
		}
		else if (newY > 0 && config->map[config->yPos + 1][config->xPos])
			newY -= 3;
		config->yOffset = newY;
		
	}
	
	else if (keydata.key == MLX_KEY_LEFT)
	{
		config->viewAngle--;
		if (config->viewAngle < 0)
			config->viewAngle = 360;
		config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
		config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		if (config->viewAngle > 360)
			config->viewAngle = 0;
		config->viewAngle++;
		config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
		config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	}
	redraw_image(config);
}