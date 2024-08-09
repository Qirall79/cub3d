/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:42:18 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	rotate(t_config *config, float rot_speed)
{
	if (config->rotate_left)
	{
		config->view_angle = normalize_angle(config->view_angle - rot_speed);
		config->dir_y = sin(config->view_angle * DEG_TO_RAD);
		config->dir_x = cos(config->view_angle * DEG_TO_RAD);
	}
	if (config->rotate_right)
	{
		config->view_angle = normalize_angle(config->view_angle + rot_speed);
		config->dir_y = sin(config->view_angle * DEG_TO_RAD);
		config->dir_x = cos(config->view_angle * DEG_TO_RAD);
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
