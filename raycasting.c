/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:18:53 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/10 11:28:41 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector dda_casting(t_config *config, float alpha)
{
	t_vector player = {config->player.x, config->player.x};
	t_vector rayDir = {cos(alpha * DEG_TO_RAD), sin(alpha * DEG_TO_RAD)};
	t_vector step;
	t_vector sideDist;
	t_vector deltaDist;
	t_vector mapCheck = player;
	t_vector p;

	normalize_vector(&rayDir);

	deltaDist.x = sqrtf(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x));
	deltaDist.y = sqrtf(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y));
	
	if (rayDir.x < 0)
	{
		step.x = -1;
		sideDist.x = (player.x - mapCheck.x) * deltaDist.x;
	}
	else
	{
		step.x = 1;
		sideDist.x = (mapCheck.x + 1.0 - player.x) * deltaDist.x;
	}
	
	if (rayDir.y < 0)
	{
		step.y = -1;
		sideDist.y = (player.y - mapCheck.y) * deltaDist.y;
	}
	else
	{
		step.y = 1;
		sideDist.y = (mapCheck.y + 1.0 - player.y) * deltaDist.y;
	}

	int wallFound = 0;
	float distance;
	distance = 1;

	while (!wallFound && distance < WIDTH)
	{
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			mapCheck.x += step.x;
			distance = sideDist.x;
			p.z = 0;
		}
		else {
			sideDist.y += deltaDist.y;
			mapCheck.y += step.y;
			distance = sideDist.y;
			p.z = 1;
		}
		
		if (in_range(mapCheck.x, 0, WIDTH) && in_range(mapCheck.y, 0, HEIGHT))
		{
			if (config->map[(int)mapCheck.y / UNIT][(int)mapCheck.x / UNIT] && config->map[(int)mapCheck.y / UNIT][(int)mapCheck.x / UNIT] != 5)
				wallFound = 1;
		}
		else
			break ;
	}
	
	p.x = distance;
	return p;
}