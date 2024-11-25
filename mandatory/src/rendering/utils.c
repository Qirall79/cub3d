/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:58:23 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/12 20:32:07 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	get_wall_height(t_config *config, float distance, float alpha)
{
	float	plane_dist;
	float	correct_dist;
	float	wall_height;

	plane_dist = config->width
		/ (2.0 * tan((config->fov_angle / 2) * DEG_TO_RAD));
	correct_dist = distance * cos((config->view_angle - alpha) * DEG_TO_RAD);
	wall_height = roundf(fabs(UNIT / correct_dist) * plane_dist);
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

	color = 0;
	if (!in_range(texture_pos.y, 0, UNIT - 1)
		|| !in_range(texture_pos.x, 0, UNIT - 1))
		return (0);
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
