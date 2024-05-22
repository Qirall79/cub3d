/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:39:50 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/22 19:28:16 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_wall_height(t_config *config, float distance, float alpha, int x)
{
	float	plane_dist;
	float	correct_dist;
	float	wall_height;

	plane_dist = config->width
		/ (2.0 * tan((config->fovAngle / 2) * DEG_TO_RAD));
	correct_dist = distance * cos((config->viewAngle - alpha) * DEG_TO_RAD);
	wall_height = roundf(fabs(UNIT / correct_dist) * plane_dist);
	config->rays[x] = distance;
	return (wall_height);
}

void	draw_ceiling_floor(t_config *config, int start_y, int end_y, int x)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		mlx_put_pixel(config->img, x, y, 0x0F00FF4F);
		y++;
	}
	y = end_y;
	while (y < config->height)
	{
		mlx_put_pixel(config->img, x, y, 0xFF0F000F);
		y++;
	}
}

t_vector	get_map_pos(t_config *config, t_vector p, float alpha)
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
	t_vector	map_pos;

	color = 0;
	map_pos = get_map_pos(config, p, alpha);
	if (!in_range(texture_pos.y, 0, UNIT - 1)
		|| !in_range(texture_pos.x, 0, UNIT - 1))
		return (0);
	if (config->map[(int)map_pos.y][(int)map_pos.x] == 4)
		color = config->door_texture[(int)texture_pos.y][(int)texture_pos.x];
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

void	draw_wall(t_config *config, t_vector p, float alpha, int x)
{
	float		wall_height;
	float		start_y;
	float		end_y;
	float		y;
	t_vector	texture_pos;

	wall_height = get_wall_height(config, p.distance, alpha, x);
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
