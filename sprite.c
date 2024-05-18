/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:01:46 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/18 14:21:07 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_drawable(t_config *config, t_vector texture_pos, t_sprite *sprite, int x)
{
	if (in_range(texture_pos.x, 0, ENEMY_SIZE)
		&& in_range(texture_pos.y, 0, ENEMY_SIZE)
		&& (char)config->sprite[(int)texture_pos.y][(int)texture_pos.x]
		&& (int)roundf(sprite->distance) <= config->rays[x])
		return (1);
	return (0);
}

void	plot_stripes(t_config *config, t_sprite *sprite)
{
	int			x;
	int			y;
	t_vector	texture_pos;

	y = sprite->start_y;
	if (y < 0)
		y = 0;
	while (y < sprite->end_y && y < HEIGHT)
	{
		x = sprite->start_x;
		if (x < 0)
			x = 0;
		while (x < sprite->end_x && x < WIDTH)
		{
			texture_pos.x = (x - sprite->start_x)
				* ((float) ENEMY_SIZE / sprite->height);
			texture_pos.y = (int)(y - sprite->start_y)
				* ((float) ENEMY_SIZE / sprite->height);
			if (is_drawable(config, texture_pos, sprite, x))
				mlx_put_pixel(config->img, x, y,
					config->sprite[(int)texture_pos.y][(int)texture_pos.x]);
			x++;
		}
		y++;
	}
}

void	get_sprite_boundaries(t_config *config, t_sprite *sprite)
{
	float	screen_angle;
	float	fov_ratio;
	float	plane_dist;

	screen_angle = ((config->fovAngle / 2.0) - sprite->angle_diff);
	fov_ratio = (float)WIDTH / config->fovAngle;
	plane_dist = WIDTH / (2 * tan(30 * DEG_TO_RAD));
	sprite->height = roundf((ENEMY_SIZE / sprite->distance) * plane_dist);
	sprite->start_y = (HEIGHT / 2) - (sprite->height / 2);
	sprite->end_y = sprite->start_y + sprite->height;
	sprite->start_x = fov_ratio * screen_angle - (sprite->height / 2);
	sprite->end_x = sprite->start_x + sprite->height;
}

void	draw_sprite(t_config *config)
{
	t_sprite	sprite;
	t_vector	diff;
	t_boundary	h;
	t_boundary	v;

	diff.x = (config->sprite_pos.x - config->xPos);
	diff.y = (config->sprite_pos.y - config->yPos);
	sprite.angle = normalize_angle(atan2(diff.y, diff.x) * (1.0 / DEG_TO_RAD));
	sprite.distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
	sprite.angle_diff = (config->viewAngle - sprite.angle);

	// if (config->sprite_offset >= 32)
	// 	config->flying_up = 1;
	// else if (config->sprite_offset <= 0)
	// 	config->flying_up = 0;
	
	// if (config->flying_up)
	// 	config->sprite_offset--;
	// else
	// 	config->sprite_offset++;

	if (in_range(config->viewAngle, 0, 90)
		&& in_range(sprite.angle, 270, 360))
		sprite.angle_diff += 360;
	if (in_range(sprite.angle, 0, 90)
		&& in_range(config->viewAngle, 270, 360))
		sprite.angle_diff -= 360;
	get_sprite_boundaries(config, &sprite);
	if (sprite.angle_diff <= (config->fovAngle / 2) + 20)
		plot_stripes(config, &sprite);
}

void draw_sprite_re(t_config *config)
{
	int y = 0;
	int x = 0;
	float sprite_angle;
	t_vector diff;

	diff.x = (config->sprite_pos.x - config->xPos);
	diff.y = (config->sprite_pos.y - config->yPos);

	sprite_angle = normalize_angle(atan2(diff.y, diff.x) * (1.0 / DEG_TO_RAD));
	float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
	float diff_angle = (config->viewAngle - sprite_angle);

	if (in_range(config->viewAngle, 0, 90) && in_range(sprite_angle, 270, 360))
		diff_angle += 360;
	if (in_range(sprite_angle, 0, 90) && in_range(config->viewAngle, 270, 360))
		diff_angle -= 360;
	
	float screen_angle = ((config->fovAngle / 2.0) - diff_angle);
	float fov_ratio = (float)WIDTH / config->fovAngle;
	float plane_dist = WIDTH / (2 * tan(30 * DEG_TO_RAD));
	float sprite_height = roundf((ENEMY_SIZE / distance) * plane_dist);
	int startY = (HEIGHT / 2) - (sprite_height / 2);
	int endY = startY + sprite_height;
	int startX = fov_ratio * screen_angle;
	int endX = startX + sprite_height;
	int texture_x;
	int texture_y;

	y = startY;
	if (y < 0)
		y = 0;
	if (diff_angle <= config->fovAngle + 10)
	{
		while (y < endY && y < HEIGHT)
		{
			x = startX;
			if (x < 0)
				x = 0;
			while (x < endX && x < WIDTH)
			{
				texture_x = (x - startX) * ((float) ENEMY_SIZE / sprite_height);
				texture_y = (int)(y - startY) * ((float) ENEMY_SIZE / sprite_height);
				if (texture_x < ENEMY_SIZE && texture_y < ENEMY_SIZE
				&& (char)config->sprite[texture_y][texture_x] != 0
				&& distance <= config->rays[x])
					mlx_put_pixel(config->img, x, y, config->sprite[texture_y][texture_x]);
				x++;
			}
			y++;
		}
	}
}
