/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:19:01 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 14:05:38 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	in_range(int p, int min, int max)
{
	return (p >= min && p <= max);
}

void	normalize_vector(t_vector *vec)
{
	float	length;

	length = sqrtf(vec->x * vec->x + vec->y * vec->y);
	vec->x = vec->x / length;
	vec->y = vec->y / length;
}

float	get_distance(float xi, float yi, float xf, float yf)
{
	return (sqrtf((xi - xf) * (xi - xf) + (yi - yf) * (yi - yf)));
}
