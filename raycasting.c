/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:18:53 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/08 18:19:01 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector dda_casting(t_config *config, float alpha)
{
	int unit = WIDTH / MAP_WIDTH;
	t_vector player = {config->xPos, config->yPos};
	t_vector rayDir = {cos(alpha * M_PI / 180), sin(alpha * M_PI / 180)};
	t_vector step;
	t_vector rayLength;
	t_vector rayUnitStep;
	t_vector mapCheck = player;
	t_vector p;

	normalize_vector(&rayDir);

	rayUnitStep.x = sqrtf(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x));
	rayUnitStep.y = sqrtf(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y));
	
	if (rayDir.x < 0)
	{
		step.x = -1;
		rayLength.x = (player.x - mapCheck.x) * rayUnitStep.x;
	}
	else
	{
		step.x = 1;
		rayLength.x = (mapCheck.x + 1 - player.x) * rayUnitStep.x;
	}
	
	if (rayDir.y < 0)
	{
		step.y = -1;
		rayLength.y = (player.y - mapCheck.y) * rayUnitStep.y;
	}
	else
	{
		step.y = 1;
		rayLength.y = (mapCheck.y + 1 - player.y) * rayUnitStep.y;
	}

	int wallFound = 0;
	float distance;
	distance = 0;

	while (!wallFound && distance < WIDTH)
	{
		if (rayLength.x < rayLength.y)
		{
			mapCheck.x += step.x;
			distance = rayLength.x;
			rayLength.x += rayUnitStep.x;
			p.z = 0;
		}
		else {
			mapCheck.y += step.y;
			distance = rayLength.y;
			rayLength.y += rayUnitStep.y;
			p.z = 1;
		}
		
		if (in_range(mapCheck.x, 0, WIDTH) && in_range(mapCheck.y, 0, HEIGHT))
		{
			if (config->map[(int)mapCheck.y / unit][(int)mapCheck.x / unit] && config->map[(int)mapCheck.y / unit][(int)mapCheck.x / unit] != 5)
				wallFound = 1;
		}
		else
			break ;
		p.x = player.x + rayDir.x * distance;
		p.y = player.y + rayDir.y * distance;
		draw_point(config, p.x, p.y);
	}

	p.x = player.x + rayDir.x * distance;
	p.y = player.y + rayDir.y * distance;
	return p;
}