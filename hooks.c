/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/03 17:33:07 by wbelfatm         ###   ########.fr       */
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
		newY = sin(config->viewAngle * M_PI / 180);
		newX = cos(config->viewAngle * M_PI / 180);
		
		// check if newX + xOffset + playerX hits a wall
		// check if newy + yOffset + playery hits a wall

		// check if part of the player hits a wall
			// if xOffset + newX > 0
				// check that the [y - 1][x + 1] and [y + 1][x + 1] aren't walls
			// if xOffset + newX < 0
				// check that the [y - 1][x - 1] and [y + 1][x - 1] aren't walls
			// if yOffset + newY > 0
				// check that the [y + 1][x + 1] and [y + 1][x - 1] aren't walls
			// if yOffset + newY < 0
				// check that the [y - 1][x + 1] and [y - 1][x - 1] aren't walls

		if (fabs(config->xOffset + newX) > 0)
		{
			if (config->xOffset + newX > 0.0001
			&& (config->map[config->yPos - 1][config->xPos + 1] || config->map[config->yPos + 1][config->xPos + 1]))
				return (printf("1: %f, %i\n", config->xOffset + newX, config->map[config->yPos][config->xPos]), free(NULL));
			if (config->xOffset + newX < -0.0001
			&& (config->map[config->yPos - 1][config->xPos - 1] || config->map[config->yPos + 1][config->xPos - 1]))
				return (printf("2: %f, %i\n", config->xOffset + newX, div), free(NULL));
		}

		if (fabs(config->yOffset + newY) > 0)
		{
			if (config->yOffset + newY > 0.0001
			&& (config->map[config->yPos + 1][config->xPos - 1] || config->map[config->yPos + 1][config->xPos + 1]))
				return (printf("3\n"), free(NULL));
			if (config->yOffset + newY < -0.0001
			&& (config->map[config->yPos - 1][config->xPos - 1] || config->map[config->yPos - 1][config->xPos + 1]))
				return (printf("4\n"), free(NULL));
		}

		config->yOffset += newY;
		config->xOffset += newX;

		// check if the offset is bigger than the div, if so, change player in map
		if (fabs(config->yOffset) >= div)
		{
			if (config->yOffset > 0.0001 && !config->map[config->yPos + 1][config->xPos])
			{
				config->map[config->yPos + 1][config->xPos] = 5;
				config->map[config->yPos][config->xPos] = 0;
				config->yPos++;
				config->yOffset -= div;
			}
			else if (config->yOffset < -0.0001 && !config->map[config->yPos - 1][config->xPos])
			{
				config->map[config->yPos - 1][config->xPos] = 5;
				config->map[config->yPos][config->xPos] = 0;
				config->yPos--;
				config->yOffset -= div;
			}
		}
	}
	else if (keydata.key == MLX_KEY_S)
	{
		newY = sin(config->viewAngle * M_PI / 180);
		newX = cos(config->viewAngle * M_PI / 180);
		config->yOffset -= newY;
		config->xOffset -= newX;
		
		if (config->xOffset)
		{
			if (config->xOffset > 0.0001
			&& (config->map[config->yPos - 1][config->xPos + 1] || config->map[config->yPos + 1][config->xPos + 1]))
				return (printf("1: %f, %i\n", config->xOffset, config->xOffset > 0), free(NULL));
			if (config->xOffset < -0.0001
			&& (config->map[config->yPos - 1][config->xPos - 1] || config->map[config->yPos + 1][config->xPos - 1]))
				return (printf("2: %f, %i\n", config->xOffset, div), free(NULL));
		}
		
		if (config->yOffset)
		{
			if (config->yOffset > 0.0001
			&& (config->map[config->yPos + 1][config->xPos - 1] || config->map[config->yPos + 1][config->xPos + 1]))
				return (printf("3\n"), free(NULL));
			if (config->yOffset < -0.0001
			&& (config->map[config->yPos - 1][config->xPos - 1] || config->map[config->yPos - 1][config->xPos + 1]))
				return (printf("4\n"), free(NULL));
		}			

		// check if the offset is bigger than the div, if so, change player in map
		if (fabs(config->yOffset) >= div)
		{
			if (config->yOffset > 0.0001 && !config->map[config->yPos + 1][config->xPos])
			{
				config->map[config->yPos + 1][config->xPos] = 5;
				config->map[config->yPos][config->xPos] = 0;
				config->yPos++;
				config->yOffset += div;
			}
			else if (config->yOffset < -0.0001 && !config->map[config->yPos - 1][config->xPos])
			{
				config->map[config->yPos - 1][config->xPos] = 5;
				config->map[config->yPos][config->xPos] = 0;
				config->yPos--;
				config->yOffset += div;
			}
		}
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