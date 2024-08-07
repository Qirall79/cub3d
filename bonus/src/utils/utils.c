/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:29:38 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/07 14:01:09 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	vertical_facing(float angle)
{
	if (sin(angle * DEG_TO_RAD) > 0.000001f)
		return (1);
	else if (sin(angle * DEG_TO_RAD) < -0.000001f)
		return (2);
	return (0);
}

int	horizontal_facing(float angle)
{
	if (cos(angle * DEG_TO_RAD) > 0.000001f)
		return (1);
	else if (cos(angle * DEG_TO_RAD) < -0.000001f)
		return (2);
	return (0);
}

void	set_failure(t_config *config)
{
	config->fail = true;
}
