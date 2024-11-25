/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:11:20 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:41:24 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	set_params_h(t_config *config, t_vector *a, t_vector *step, float alpha)
{
	float	a_tan;

	a_tan = -1.0f / tan(alpha * DEG_TO_RAD);
	if (vertical_facing(alpha) == DOWN)
	{
		a->y = floorf(config->y_pos / UNIT) * UNIT + UNIT;
		step->y = UNIT;
		step->x = -step->y * a_tan;
	}
	else if (vertical_facing(alpha) == TOP)
	{
		a->y = floorf(config->y_pos / UNIT) * UNIT;
		step->y = -UNIT;
		step->x = -step->y * a_tan;
	}
	else
		return (0);
	if (step->x > 0 && horizontal_facing(alpha) == LEFT)
		step->x *= -1;
	if (step->x < 0 && horizontal_facing(alpha) == RIGHT)
		step->x *= -1;
	a->x = config->x_pos + (config->y_pos - a->y) * a_tan;
	return (1);
}

int	set_params_v(t_config *config, t_vector *a, t_vector *step, float alpha)
{
	float	a_tan;

	a_tan = -tan(alpha * DEG_TO_RAD);
	if (horizontal_facing(alpha) == RIGHT)
	{
		a->x = floorf(config->x_pos / UNIT) * UNIT + UNIT;
		step->x = UNIT;
		step->y = -step->x * a_tan;
	}
	else if (horizontal_facing(alpha) == LEFT)
	{
		a->x = floorf(config->x_pos / UNIT) * UNIT;
		step->x = -UNIT;
		step->y = -step->x * a_tan;
	}
	else
		return (0);
	if (step->y > 0 && vertical_facing(alpha) == TOP)
		step->y *= -1;
	if (step->y < 0 && vertical_facing(alpha) == DOWN)
		step->y *= -1;
	a->y = config->y_pos + (config->x_pos - a->x) * a_tan;
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
