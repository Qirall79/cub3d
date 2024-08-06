/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/06 10:56:05 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
