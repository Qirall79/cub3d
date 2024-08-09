/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:14:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:42:43 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_map(t_config *config)
{
	if (config->fail)
		return ;
	draw_rays(config);
}

void	draw_point(t_config *config, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(config->img, x + j - 2, y + i - 2, 0xFFFF00FF);
			j++;
		}
		i++;
	}
}

void	draw_rays(t_config *config)
{
	float		min_angle;
	t_vector	p;
	int			i;

	min_angle = config->view_angle - config->fov_angle / 2;
	i = 0;
	while (i < config->width)
	{
		p = find_intersection(config, normalize_angle(min_angle));
		draw_wall(config, p, min_angle, i);
		min_angle += config->fov_angle / (float)(config->width);
		i++;
	}
}

void	draw_line(t_vector start, t_vector end,
	t_config *config, int color)
{
	int			i;
	t_vector	incr;
	t_vector	d;
	float		steps;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	steps = fabs(d.x);
	if (fabs(d.x) < fabs(d.y))
		steps = fabs(d.y);
	i = 0;
	incr.x = (float)d.x / steps;
	incr.y = (float)d.y / steps;
	while (i++ < steps)
	{
		if (start.x >= 0 && start.x < config->width
			&& start.y >= 0 && start.y < config->height)
			mlx_put_pixel(config->img, round(start.x), round(start.y), color);
		start.x += incr.x;
		start.y += incr.y;
	}
}
