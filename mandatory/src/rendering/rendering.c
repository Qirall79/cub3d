/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:39:50 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/07 14:28:40 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_ceiling_floor(t_config *config, int start_y, int end_y, int x)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		mlx_put_pixel(config->img, x, y, config->c_color);
		y++;
	}
	y = end_y;
	while (y < config->height)
	{
		mlx_put_pixel(config->img, x, y, config->f_color);
		y++;
	}
}

void	draw_wall(t_config *config, t_vector p, float alpha, int x)
{
	float		wall_height;
	float		start_y;
	float		end_y;
	float		y;
	t_vector	texture_pos;

	wall_height = get_wall_height(config, p.distance, alpha);
	start_y = (config->height / 2) - (wall_height / 2);
	end_y = start_y + wall_height;
	draw_ceiling_floor(config, start_y, end_y, x);
	texture_pos.x = get_texture_x(p);
	y = start_y;
	while (y < end_y && y < config->height)
	{
		texture_pos.y = (int)((y - start_y) * ((float) UNIT / wall_height));
		if (y < 0)
			y = 0;
		mlx_put_pixel(config->img, x, y,
			get_color(config, p, alpha, texture_pos));
		y++;
	}
}
