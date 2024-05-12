/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/12 10:01:32 by wbelfatm         ###   ########.fr       */
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

int is_wall(int cell)
{
	
	return cell > 0 && cell != 5;
}

void move_player(t_config *config)
{
	int unit;
	float newX;
	float newY;
	float movSpeed;
	float rotSpeed;
	float oldDirX;
	float oldPlaneX;

	unit = WIDTH / MAP_WIDTH;
	movSpeed = config->mlx->delta_time * 3.0;
	rotSpeed = config->mlx->delta_time * 1.0;

	// camera rotation
	if (config->rotate_right)
	{
		oldDirX = config->dir.x;
		config->dir.x = config->dir.x * cos(-rotSpeed) - config->dir.y * sin(-rotSpeed);
		config->dir.y = oldDirX * sin(-rotSpeed) + config->dir.y * cos(-rotSpeed);
		oldPlaneX = config->plane.x;
		config->plane.x = config->plane.x * cos(-rotSpeed) - config->plane.y * sin(-rotSpeed);
		config->plane.y = oldPlaneX * sin(-rotSpeed) + config->plane.y * cos(-rotSpeed);
	}
	if (config->rotate_left)
	{
		oldDirX = config->dir.x;
		config->dir.x = config->dir.x * cos(rotSpeed) - config->dir.y * sin(rotSpeed);
		config->dir.y = oldDirX * sin(rotSpeed) + config->dir.y * cos(rotSpeed);
		oldPlaneX = config->plane.x;
		config->plane.x = config->plane.x * cos(rotSpeed) - config->plane.y * sin(rotSpeed);
		config->plane.y = oldPlaneX * sin(rotSpeed) + config->plane.y * cos(rotSpeed);
	}

	// player movement
	if (config->move_left)
	{
		// todo
	}
	if (config->move_right)
	{
		// todo
	}
	int COLLISION_MARGIN = 10.0;
	if (config->move_forward)
	{
		if (!is_wall(config->map[(int)(config->player.y + config->dir.y * movSpeed * COLLISION_MARGIN)][(int)config->player.x]))
		{
			// Check if the next movement will cause a collision
			if (!is_wall(config->map[(int)(config->player.y + (config->dir.y * movSpeed) * COLLISION_MARGIN)][(int)config->player.x]))
				config->player.y += config->dir.y * movSpeed; // Move player forward
		}
		if (!is_wall(config->map[(int)config->player.y][(int)(config->player.x + config->dir.x * movSpeed)]))
		{
			// Check if the next movement will cause a collision
			if (!is_wall(config->map[(int)config->player.y][(int)(config->player.x + (config->dir.x * movSpeed) * COLLISION_MARGIN)]))
				config->player.x += config->dir.x * movSpeed; // Move player forward
		}
	}
	if (config->move_backward)
	{
		if (!is_wall(config->map[(int)(config->player.y - config->dir.y * movSpeed * COLLISION_MARGIN)][(int)config->player.x]))
		{
			// Check if the next movement will cause a collision
			if (!is_wall(config->map[(int)(config->player.y - (config->dir.y * movSpeed) * COLLISION_MARGIN)][(int)config->player.x]))
				config->player.y -= config->dir.y * movSpeed; // Move player backward
		}
		if (!is_wall(config->map[(int)config->player.y][(int)(config->player.x - config->dir.x * movSpeed)]))
		{
			// Check if the next movement will cause a collision
			if (!is_wall(config->map[(int)config->player.y][(int)(config->player.x - (config->dir.x * movSpeed) * COLLISION_MARGIN)]))
				config->player.x -= config->dir.x * movSpeed; // Move player backward
		}
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