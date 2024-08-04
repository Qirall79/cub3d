/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 11:04:25 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return (angle);
}

int	is_wall_v(float newX, float newY, t_config *config)
{
	int	x;
	int	y;

	(void) newX;
	y = (int)(config->yPos + newY) / UNIT;
	x = (int)(config->xPos) / UNIT;
	if (config->map[y][x] == 1)
		return (1);
	return (0);
}

int	is_wall_h(float newX, float newY, t_config *config)
{
	int	x;
	int	y;

	(void) newY;
	x = (int)(config->xPos + newX) / UNIT;
	y = (int)(config->yPos) / UNIT;
	if (config->map[y][x] == 1)
		return (1);
	return (0);
}

void	move_forward(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = sin(config->viewAngle * DEG_TO_RAD) * mov_speed;
	new_x = cos(config->viewAngle * DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

void	move_backward(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = -sin(config->viewAngle * DEG_TO_RAD) * mov_speed;
	new_x = -cos(config->viewAngle * DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

void	move_right(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = sin(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	new_x = cos(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

void	move_left(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = -sin(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	new_x = -cos(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

void	rotate(t_config *config, float rot_speed)
{
	if (config->rotate_left)
	{
		config->viewAngle = normalize_angle(config->viewAngle - rot_speed);
		config->dirY = sin(config->viewAngle * DEG_TO_RAD);
		config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	}
	if (config->rotate_right)
	{
		config->viewAngle = normalize_angle(config->viewAngle + rot_speed);
		config->dirY = sin(config->viewAngle * DEG_TO_RAD);
		config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	}
}

void	move_player(t_config *config)
{
	float	mov_speed;
	float	rot_speed;

	mov_speed = config->mlx->delta_time * UNIT * 3.5;
	rot_speed = config->mlx->delta_time * 100.0;
	rotate(config, rot_speed);
	if (config->move_left)
		move_left(config, mov_speed);
	if (config->move_right)
		move_right(config, mov_speed);
	if (config->move_forward)
		move_forward(config, mov_speed);
	if (config->move_backward)
		move_backward(config, mov_speed);
}

void	set_movement_params(mlx_key_data_t keydata, t_config *config)
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

void	end_game(t_config *config)
{
	mlx_terminate(config->mlx);
	free_config(config);
	exit(EXIT_SUCCESS);
}

void	handle_click(mlx_key_data_t keydata, t_config *config)
{
	set_movement_params(keydata, config);
	if (keydata.key == MLX_KEY_ESCAPE)
		end_game(config);
}

void	loop_hook(t_config *config)
{
	if (config->fail)
	{
		free_config(config);
		exit(EXIT_FAILURE);
	}
	move_player(config);
	redraw_image(config);
}
