/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/04 12:02:12 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(mlx_key_data_t keydata, t_config *config)
{
	int div;
	float newX;
	float newY;

	div = WIDTH / MAP_WIDTH;
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
		if (newX < 0 && fabs(newX) >= div
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
		if (newX > 0 && fabs(newX) >= div && !config->map[config->yPos][config->xPos + 1])
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
		newY = sin(config->viewAngle * M_PI / 180) * 2;
		newX = cos(config->viewAngle * M_PI / 180) * 2;

		int tmpX = config->xPos * div + (div - 10) / 2 + config->xOffset + newX;
		int tmpY = config->yPos * div + (div - 10) / 2 + config->yOffset + newY;
		int startX = tmpX / div;
		int endX = (tmpX + (div - 10) / 2) / div;
		int startY = tmpY / div;
		int endY = (tmpY + (div - 10) / 2) / div;

		if (config->map[config->yPos][endX] == 1 || config->map[config->yPos][startX] == 1
			|| (config->yOffset > (div - 10) / 2 && (config->map[config->yPos + 1][endX] == 1 || config->map[config->yPos + 1][startX] == 1))
			|| (config->yOffset < -((div - 10) / 2) && (config->map[config->yPos - 1][endX] == 1 || config->map[config->yPos - 1][startX] == 1)))
			return ;
		if (config->map[startY][config->xPos] == 1 || config->map[endY][config->xPos] == 1
			|| (config->xOffset > (div - 10) / 2 && (config->map[startY][config->xPos + 1] == 1 || config->map[endY][config->xPos + 1] == 1))
			|| (config->xOffset < -((div - 10) / 2) && (config->map[startY][config->xPos - 1] == 1 || config->map[endY][config->xPos - 1] == 1)))
			return ;
	
		if (startY == endY && startY != config->yPos)
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[startY][config->xPos] = 5;
			config->yPos = startY;
			if (config->yOffset > 0)
				config->yOffset = -((div - 10) / 2);
			else
				config->yOffset = ((div - 10) / 2);
		}
		else
			config->yOffset += newY;
		
		if (startX == endX && startX != config->xPos)
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[config->yPos][startX] = 5;
			config->xPos = startX;
			if (config->xOffset > 0)
				config->xOffset = -((div - 10) / 2);
			else
				config->xOffset = ((div - 10) / 2);
		}
		else
			config->xOffset += newX;
		
	}
	else if (keydata.key == MLX_KEY_S)
	{
		newY = -sin(config->viewAngle * M_PI / 180) * 2;
		newX = -cos(config->viewAngle * M_PI / 180) * 2;

		int tmpX = config->xPos * div + (div - 10) / 2 + config->xOffset + newX;
		int tmpY = config->yPos * div + (div - 10) / 2 + config->yOffset + newY;
		int startX = tmpX / div;
		int endX = (tmpX + (div - 10) / 2) / div;
		int startY = tmpY / div;
		int endY = (tmpY + (div - 10) / 2) / div;

		if (config->map[config->yPos][endX] == 1 || config->map[config->yPos][startX] == 1
			|| (config->yOffset > (div - 10) / 2 && (config->map[config->yPos + 1][endX] == 1 || config->map[config->yPos + 1][startX] == 1))
			|| (config->yOffset < -((div - 10) / 2) && (config->map[config->yPos - 1][endX] == 1 || config->map[config->yPos - 1][startX] == 1)))
			return ;
		if (config->map[startY][config->xPos] == 1 || config->map[endY][config->xPos] == 1
			|| (config->xOffset > (div - 10) / 2 && (config->map[startY][config->xPos + 1] == 1 || config->map[endY][config->xPos + 1] == 1))
			|| (config->xOffset < -((div - 10) / 2) && (config->map[startY][config->xPos - 1] == 1 || config->map[endY][config->xPos - 1] == 1)))
			return ;
	
		if (startY == endY && startY != config->yPos)
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[startY][config->xPos] = 5;
			config->yPos = startY;
			if (config->yOffset > 0)
				config->yOffset = -((div - 10) / 2);
			else
				config->yOffset = ((div - 10) / 2);
		}
		else
			config->yOffset += newY;
		
		if (startX == endX && startX != config->xPos)
		{
			config->map[config->yPos][config->xPos] = 0;
			config->map[config->yPos][startX] = 5;
			config->xPos = startX;
			if (config->xOffset > 0)
				config->xOffset = -((div - 10) / 2);
			else
				config->xOffset = ((div - 10) / 2);
		}
		else
			config->xOffset += newX;
	}
	
	else if (keydata.key == MLX_KEY_LEFT)
	{
		config->viewAngle -= 4;
		if (config->viewAngle < 0)
			config->viewAngle = 360;
		config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
		config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		config->viewAngle += 4;
		if (config->viewAngle > 360)
			config->viewAngle = 0;
		config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
		config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	}
	redraw_image(config);
}