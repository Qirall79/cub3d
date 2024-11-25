/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:20:19 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:40:41 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_forward(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = sin(config->view_angle * DEG_TO_RAD) * mov_speed;
	new_x = cos(config->view_angle * DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->x_pos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->y_pos += new_y;
	else
	{
		config->x_pos += new_x;
		config->y_pos += new_y;
	}
}

void	move_backward(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = -sin(config->view_angle * DEG_TO_RAD) * mov_speed;
	new_x = -cos(config->view_angle * DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->x_pos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->y_pos += new_y;
	else
	{
		config->x_pos += new_x;
		config->y_pos += new_y;
	}
}

void	move_right(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = sin(normalize_angle(config->view_angle + 90)
			* DEG_TO_RAD) * mov_speed;
	new_x = cos(normalize_angle(config->view_angle + 90)
			* DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->x_pos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->y_pos += new_y;
	else
	{
		config->x_pos += new_x;
		config->y_pos += new_y;
	}
}

void	move_left(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = -sin(normalize_angle(config->view_angle + 90)
			* DEG_TO_RAD) * mov_speed;
	new_x = -cos(normalize_angle(config->view_angle + 90)
			* DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->x_pos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->y_pos += new_y;
	else
	{
		config->x_pos += new_x;
		config->y_pos += new_y;
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
