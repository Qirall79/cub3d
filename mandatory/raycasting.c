/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:18:53 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 11:00:44 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_params_h(t_config *config, t_vector *a, t_vector *step, float alpha)
{
	float	a_tan;

	a_tan = -1.0f / tan(alpha * DEG_TO_RAD);
	if (vertical_facing(alpha) == DOWN)
	{
		a->y = floorf(config->yPos / UNIT) * UNIT + UNIT;
		step->y = UNIT;
		step->x = -step->y * a_tan;
	}
	else if (vertical_facing(alpha) == TOP)
	{
		a->y = floorf(config->yPos / UNIT) * UNIT;
		step->y = -UNIT;
		step->x = -step->y * a_tan;
	}
	else
		return (0);
	if (step->x > 0 && horizontal_facing(alpha) == LEFT)
		step->x *= -1;
	if (step->x < 0 && horizontal_facing(alpha) == RIGHT)
		step->x *= -1;
	a->x = config->xPos + (config->yPos - a->y) * a_tan;
	return (1);
}

int	set_params_v(t_config *config, t_vector *a, t_vector *step, float alpha)
{
	float	a_tan;

	a_tan = -tan(alpha * DEG_TO_RAD);
	if (horizontal_facing(alpha) == RIGHT)
	{
		a->x = floorf(config->xPos / UNIT) * UNIT + UNIT;
		step->x = UNIT;
		step->y = -step->x * a_tan;
	}
	else if (horizontal_facing(alpha) == LEFT)
	{
		a->x = floorf(config->xPos / UNIT) * UNIT;
		step->x = -UNIT;
		step->y = -step->x * a_tan;
	}
	else
		return (0);
	if (step->y > 0 && vertical_facing(alpha) == TOP)
		step->y *= -1;
	if (step->y < 0 && vertical_facing(alpha) == DOWN)
		step->y *= -1;
	a->y = config->yPos + (config->xPos - a->x) * a_tan;
	return (1);
}

int	check_wall_hit(t_config *config, t_vector map_pos)
{
	if (!(in_range(map_pos.x, 0, config->map_width - 1)
			&& in_range(map_pos.y, 0, config->map_height - 1)))
		return (0);
	if (config->map[(int)map_pos.y][(int)map_pos.x] == 1)
		return (1);
	return (0);
}

t_vector	raycasting_h(t_config *config, float alpha)
{
	t_vector	a;
	t_vector	step;
	t_vector	map_pos;
	int			i;

	a.x = config->xPos;
	a.y = config->yPos;
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

	a.x = config->xPos;
	a.y = config->yPos;
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
	dist_h = sqrtf((config->xPos - p_h.x) * (config->xPos - p_h.x)
			+ (config->yPos - p_h.y) * (config->yPos - p_h.y));
	dist_v = sqrtf((config->xPos - p_v.x) * (config->xPos - p_v.x)
			+ (config->yPos - p_v.y) * (config->yPos - p_v.y));
	if (p_v.x == config->xPos && p_v.y == config->yPos)
		dist_v = 1e9;
	if (p_h.x == config->xPos && p_h.y == config->yPos)
		dist_h = 1e9;
	p_h.distance = dist_h;
	p_v.distance = dist_v;
	if (dist_h <= dist_v)
		return (p_h);
	return (p_v);
}
