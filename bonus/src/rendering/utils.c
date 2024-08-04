/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:58:23 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 23:01:53 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	get_wall_height(t_config *config, float distance, float alpha, int x)
{
	float	plane_dist;
	float	correct_dist;
	float	wall_height;

	plane_dist = config->width
		/ (2.0 * tan((config->fovAngle / 2) * DEG_TO_RAD));
	correct_dist = distance * cos((config->viewAngle - alpha) * DEG_TO_RAD);
	wall_height = roundf(fabs(UNIT / correct_dist) * plane_dist);
	config->rays[x] = distance;
	return (wall_height);
}

t_vector	get_map_pos(t_vector p, float alpha)
{
	t_vector	map_pos;

	map_pos.x = floorf((p.x) / UNIT);
	map_pos.y = floorf((p.y) / UNIT);
	if (p.z && horizontal_facing(alpha) == LEFT)
		map_pos.x--;
	if (!p.z && vertical_facing(alpha) == TOP)
		map_pos.y--;
	return (map_pos);
}

int	get_color(t_config *config, t_vector p, float alpha, t_vector texture_pos)
{
	int			color;
	t_vector	map_pos;

	color = 0;
	map_pos = get_map_pos(p, alpha);
	if (!in_range(texture_pos.y, 0, UNIT - 1)
		|| !in_range(texture_pos.x, 0, UNIT - 1))
		return (0);
	if (config->map[(int)map_pos.y][(int)map_pos.x] == 4)
		color = config->door_texture[(int)texture_pos.y][(int)texture_pos.x];
	else if (p.z && horizontal_facing(alpha) == LEFT)
		color = config->texture_east[(int)texture_pos.y][(int)texture_pos.x];
	else if (p.z && horizontal_facing(alpha) == RIGHT)
		color = config->texture_west[(int)texture_pos.y][(int)texture_pos.x];
	else if (!p.z && vertical_facing(alpha) == TOP)
		color = config->texture_north[(int)texture_pos.y][(int)texture_pos.x];
	else if (!p.z && vertical_facing(alpha) == DOWN)
		color = config->texture_south[(int)texture_pos.y][(int)texture_pos.x];
	return (color);
}

int	get_texture_x(t_vector p)
{
	if (p.z)
		return ((int)p.y % UNIT);
	return ((int)p.x % UNIT);
}
