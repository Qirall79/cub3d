/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/05 10:33:36 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_player(t_config *config)
{
	int div;
	float newX;
	float newY;

	div = WIDTH / MAP_WIDTH;
	if (config->move_left)
	{
		newY = sin((config->viewAngle - 90) * M_PI / 180) * 2;
		newX = cos((config->viewAngle - 90) * M_PI / 180) * 2;

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
	if (config->move_right)
	{
		newY = sin((config->viewAngle + 90) * M_PI / 180) * 2;
		newX = cos((config->viewAngle + 90) * M_PI / 180) * 2;

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
	if (config->move_forward)
	{
		printf("hello\n");
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
	if (config->move_backward)
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
	
	if (config->rotate_left)
	{
		config->viewAngle -= 4;
		if (config->viewAngle < 0)
			config->viewAngle = 360;
		config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
		config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	}
	if (config->rotate_right)
	{
		config->viewAngle += 4;
		if (config->viewAngle > 360)
			config->viewAngle = 0;
		config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
		config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	}
	// redraw_image(config);
}

void set_movement_params(mlx_key_data_t keydata, t_config *config)
{
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		config->move_forward = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		config->move_forward = 0;
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		config->move_backward = 1;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		config->move_backward = 0;
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		config->move_right = 1;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		config->move_right = 0;
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		config->move_left = 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		config->move_left = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
		config->rotate_right = 1;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		config->rotate_right = 0;
	if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
		config->rotate_left = 1;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		config->rotate_left = 0;
}

void loop_hook(t_config *config)
{
	move_player(config);
	redraw_image(config);
}