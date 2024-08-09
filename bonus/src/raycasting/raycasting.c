/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:18:53 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:08:57 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_vector	raycasting_h(t_config *config, float alpha)
{
	t_vector	a;
	t_vector	step;
	t_vector	map_pos;
	int			i;

	a.x = config->x_pos;
	a.y = config->y_pos;
	if (!set_params_h(config, &a, &step, alpha))
		return (a);
	i = 0;
	while (i < MAX_CHECK)
	{
		map_pos.x = (int) a.x / UNIT;
		map_pos.y = (int) a.y / UNIT;
		if (vertical_facing(alpha) == TOP)
			map_pos.y = (int)(a.y - 1) / UNIT;
		if (check_wall_hit(config, map_pos))
			break ;
		a.x += step.x;
		a.y += step.y;
		i++;
	}
	return (a);
}

t_vector	raycasting_v(t_config *config, float alpha)
{
	t_vector	a;
	t_vector	step;
	t_vector	map_pos;
	int			i;

	a.x = config->x_pos;
	a.y = config->y_pos;
	if (!set_params_v(config, &a, &step, alpha))
		return (a);
	i = 0;
	while (i < MAX_CHECK)
	{
		map_pos.x = (int) a.x / UNIT;
		if (horizontal_facing(alpha) == LEFT)
			map_pos.x = (int)(a.x - 1) / UNIT;
		map_pos.y = (int) a.y / UNIT;
		if (check_wall_hit(config, map_pos))
			break ;
		a.x += step.x;
		a.y += step.y;
		i++;
	}
	return (a);
}

t_vector	find_intersection(t_config *config, float alpha)
{
	t_vector	p_h;
	t_vector	p_v;
	float		dist_h;
	float		dist_v;

	p_h = raycasting_h(config, alpha);
	p_v = raycasting_v(config, alpha);
	p_v.z = 1;
	p_h.z = 0;
	dist_h = sqrtf((config->x_pos - p_h.x) * (config->x_pos - p_h.x)
			+ (config->y_pos - p_h.y) * (config->y_pos - p_h.y));
	dist_v = sqrtf((config->x_pos - p_v.x) * (config->x_pos - p_v.x)
			+ (config->y_pos - p_v.y) * (config->y_pos - p_v.y));
	if ((p_v.x == config->x_pos && p_v.y == config->y_pos)
		|| (dist_v < 0.00001 && dist_v > -0.00001))
		dist_v = 1e9;
	if ((p_h.x == config->x_pos && p_h.y == config->y_pos)
		|| (dist_h < 0.00001 && dist_h > -0.00001))
		dist_h = 1e9;
	p_h.distance = dist_h;
	p_v.distance = dist_v;
	if (dist_h <= dist_v)
		return (p_h);
	return (p_v);
}
