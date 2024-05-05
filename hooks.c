/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/05 11:51:21 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float normalize_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return angle;
}

int is_wall_v(float newX, float newY, t_config *config)
{
	int unit = WIDTH / MAP_WIDTH;
	
	if (config->map[(int)(config->yPos - 5 + newY) / unit][(int)(config->xPos - 5) / unit] == 1
	|| config->map[(int)(config->yPos + 5 + newY) / unit][(int)(config->xPos + 5) / unit] == 1
	|| config->map[(int)(config->yPos - 5 + newY) / unit][(int)(config->xPos + 5) / unit] == 1
	|| config->map[(int)(config->yPos + 5 + newY) / unit][(int)(config->xPos - 5) / unit] == 1)
		return 1;
	return 0;
}
int is_wall_h(float newX, float newY, t_config *config)
{
	int unit = WIDTH / MAP_WIDTH;
	
	if (config->map[(int)(config->yPos - 5) / unit][(int)(config->xPos - 5 + newX) / unit] == 1
	|| config->map[(int)(config->yPos + 5) / unit][(int)(config->xPos + 5 + newX) / unit] == 1
	|| config->map[(int)(config->yPos - 5) / unit][(int)(config->xPos + 5 + newX) / unit] == 1
	|| config->map[(int)(config->yPos + 5) / unit][(int)(config->xPos - 5 + newX) / unit] == 1)
		return 1;
	return 0;
}

void move_player(t_config *config)
{
	int unit;
	float newX;
	float newY;

	unit = WIDTH / MAP_WIDTH;
	if (config->move_left)
	{
		newY = sin((normalize_angle(config->viewAngle - 90)) * M_PI / 180) * 2;
		newX = cos((normalize_angle(config->viewAngle - 90)) * M_PI / 180) * 2;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->xPos += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->yPos += newY;
			return ;
		}

		config->xPos += newX;
		config->yPos += newY;
	}
	if (config->move_right)
	{
		newY = sin(normalize_angle(config->viewAngle + 90) * M_PI / 180) * 2;
		newX = cos(normalize_angle(config->viewAngle + 90) * M_PI / 180) * 2;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->xPos += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->yPos += newY;
			return ;
		}
		config->xPos += newX;
		config->yPos += newY;
	}
	if (config->move_forward)
	{
		newY = sin(config->viewAngle * M_PI / 180) * 2;
		newX = cos(config->viewAngle * M_PI / 180) * 2;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->xPos += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->yPos += newY;
			return ;
		}
		config->xPos += newX;
		config->yPos += newY;
	}
	if (config->move_backward)
	{
		newY = -sin(config->viewAngle * M_PI / 180) * 2;
		newX = -cos(config->viewAngle * M_PI / 180) * 2;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->xPos += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->yPos += newY;
			return ;
		}
		config->xPos += newX;
		config->yPos += newY;
	}

	if (config->rotate_left)
	{
		config->viewAngle = normalize_angle(config->viewAngle - 4);
		config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
		config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	}
	if (config->rotate_right)
	{
		config->viewAngle = normalize_angle(config->viewAngle + 4);
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