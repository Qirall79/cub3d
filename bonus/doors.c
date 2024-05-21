/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:58:23 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/21 10:52:54 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int door_visible(t_config *config, t_vector door_pos)
{
	t_vector diff;
	float angle;
	float angle_diff;

	diff.x = ((door_pos.x * UNIT + UNIT / 2) - config->xPos);
	diff.y = ((door_pos.x * UNIT + UNIT / 2) - config->yPos);
	angle = normalize_angle(atan2(diff.y, diff.x) * (1.0 / DEG_TO_RAD));
	angle_diff = (config->viewAngle - angle);

	if (in_range(config->viewAngle, 0, 90)
		&& in_range(angle, 270, 360))
		angle_diff += 360;
	if (in_range(angle, 0, 90)
		&& in_range(config->viewAngle, 270, 360))
		angle_diff -= 360;
	if (fabs(angle_diff) <= config->fovAngle / 2)
		return (1);
	return (0);
}

t_vector check_door(t_config *config)
{
	t_vector player_pos;
	t_vector door_pos;
	int i;
	int j;

	player_pos.x = floorf(config->xPos / UNIT);
	player_pos.y = floorf(config->yPos / UNIT);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (!in_range(player_pos.y + i, 0, config->map_height - 1)
			|| !in_range(player_pos.x + j, 0, config->map_width - 1))
			{
				j++;
				continue ;
			}
			if (config->map[(int)player_pos.y + i][(int)player_pos.x + j] == 4
			|| config->map[(int)player_pos.y + i][(int)player_pos.x + j] == 6)
			{
				door_pos.y = player_pos.y + i;
				door_pos.x = player_pos.x + j;
				if (door_visible(config, door_pos))
					return (door_pos);
			}
			j++;
		}
		i++;
	}
	door_pos.x = -1;
	return (door_pos);
	
}

// t_vector check_door(t_config *config)
// {
// 	t_vector player_pos;
// 	t_vector door_pos;
// 	t_vector diff;
// 	float angle;
// 	float angle_diff;

// 	player_pos.x = floorf(config->xPos / UNIT);
// 	player_pos.y = floorf(config->yPos / UNIT);

// 	door_pos.x = -1;
// 	door_pos.y = -1;

// 	if (player_pos.x < config->map_width - 1
// 	&& (config->map[(int)player_pos.y][(int)player_pos.x + 1] == 4
// 		|| config->map[(int)player_pos.y][(int)player_pos.x + 1] == 6))
// 	{
// 		door_pos.x = player_pos.x + 1;
// 		door_pos.y = player_pos.y;
// 	}
// 	if (player_pos.x > 0 && (config->map[(int)player_pos.y][(int)player_pos.x - 1] == 4
// 		|| config->map[(int)player_pos.y][(int)player_pos.x - 1] == 6))
// 	{
// 		door_pos.x = player_pos.x - 1;
// 		door_pos.y = player_pos.y;
// 	}
// 	if (player_pos.y > 0 && (config->map[(int)player_pos.y - 1][(int)player_pos.x] == 4
// 		|| config->map[(int)player_pos.y - 1][(int)player_pos.x] == 6))
// 	{
// 		door_pos.x = player_pos.x;
// 		door_pos.y = player_pos.y - 1;
// 	}
// 	if (player_pos.y < config->map_height - 1 && (config->map[(int)player_pos.y + 1][(int)player_pos.x] == 4
// 		|| config->map[(int)player_pos.y + 1][(int)player_pos.x] == 6))
// 	{
// 		door_pos.x = player_pos.x;
// 		door_pos.y = player_pos.y + 1;
// 	}

// 	if (door_pos.x == -1)
// 		return door_pos;

// 	// check if it's in fov
// 	diff.x = ((door_pos.x * UNIT + UNIT / 2) - config->xPos);
// 	diff.y = ((door_pos.x * UNIT + UNIT / 2) - config->yPos);
// 	angle = normalize_angle(atan2(diff.y, diff.x) * (1.0 / DEG_TO_RAD));
// 	angle_diff = (config->viewAngle - angle);

// 	if (in_range(config->viewAngle, 0, 90)
// 		&& in_range(angle, 270, 360))
// 		angle_diff += 360;
// 	if (in_range(angle, 0, 90)
// 		&& in_range(config->viewAngle, 270, 360))
// 		angle_diff -= 360;
// 	if (fabs(angle_diff) > config->fovAngle / 2 + 20)
// 		door_pos.x = -1;
// 	return door_pos;
// }