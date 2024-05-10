/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/10 11:28:27 by wbelfatm         ###   ########.fr       */
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
	
	if (config->map[(int)(config->player.y - 5 + newY) / unit][(int)(config->player.x - 5) / unit] == 1
	|| config->map[(int)(config->player.y + 5 + newY) / unit][(int)(config->player.x + 5) / unit] == 1
	|| config->map[(int)(config->player.y - 5 + newY) / unit][(int)(config->player.x + 5) / unit] == 1
	|| config->map[(int)(config->player.y + 5 + newY) / unit][(int)(config->player.x - 5) / unit] == 1)
		return 1;
	return 0;
}
int is_wall_h(float newX, float newY, t_config *config)
{
	int unit = WIDTH / MAP_WIDTH;
	
	if (config->map[(int)(config->player.y - 5) / unit][(int)(config->player.x - 5 + newX) / unit] == 1
	|| config->map[(int)(config->player.y + 5) / unit][(int)(config->player.x + 5 + newX) / unit] == 1
	|| config->map[(int)(config->player.y - 5) / unit][(int)(config->player.x + 5 + newX) / unit] == 1
	|| config->map[(int)(config->player.y + 5) / unit][(int)(config->player.x - 5 + newX) / unit] == 1)
		return 1;
	return 0;
}

void move_player(t_config *config)
{
	int unit;
	float newX;
	float newY;

	unit = WIDTH / MAP_WIDTH;

	// camera rotation
	if (config->rotate_left)
	{
		config->viewAngle = normalize_angle(config->viewAngle - 1);
		config->dir.y = sin(config->viewAngle * DEG_TO_RAD);
		config->dir.x = cos(config->viewAngle * DEG_TO_RAD);
	}
	if (config->rotate_right)
	{
		config->viewAngle = normalize_angle(config->viewAngle + 1);
		config->dir.y = sin(config->viewAngle * DEG_TO_RAD);
		config->dir.x = cos(config->viewAngle * DEG_TO_RAD);
	}

	// player movement
	if (config->move_left)
	{
		newY = roundf(sin((normalize_angle(config->viewAngle - 90)) * DEG_TO_RAD));
		newX = roundf(cos((normalize_angle(config->viewAngle - 90)) * DEG_TO_RAD));

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->player.x += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->player.y += newY;
			return ;
		}

		config->player.x += newX;
		config->player.y += newY;
	}
	if (config->move_right)
	{
		newY = roundf(sin(normalize_angle(config->viewAngle + 90) * DEG_TO_RAD));
		newX = roundf(cos(normalize_angle(config->viewAngle + 90) * DEG_TO_RAD));

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->player.x += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->player.y += newY;
			return ;
		}
		config->player.x += newX;
		config->player.y += newY;
	}
	if (config->move_forward)
	{
		newY = sin(config->viewAngle * DEG_TO_RAD) * 2;
		newX = cos(config->viewAngle * DEG_TO_RAD) * 2;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->player.x += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->player.y += newY;
			return ;
		}
		config->player.x += newX;
		config->player.y += newY;
	}
	if (config->move_backward)
	{
		newY = -sin(config->viewAngle * DEG_TO_RAD) * 2;
		newX = -cos(config->viewAngle * DEG_TO_RAD) * 2;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
		{
			config->player.x += newX;
			return ;
		}
		if (is_wall_h(newX, newY, config))
		{
			config->player.y += newY;
			return ;
		}
		config->player.x += newX;
		config->player.y += newY;
	}
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