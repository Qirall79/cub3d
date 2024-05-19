/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:01:46 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/19 12:26:13 by wbelfatm         ###   ########.fr       */
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

void move_sprite(t_config *config)
{
	t_vector map_pos;
	t_vector player_pos;
	t_vector next_step;
	float mov_speed = config->mlx->delta_time * UNIT * 2.0;

	map_pos.x = floorf(config->sprite_pos.x / UNIT);
	map_pos.y = floorf(config->sprite_pos.y / UNIT);
	player_pos.x = floorf(config->xPos / UNIT);
	player_pos.y = floorf(config->yPos / UNIT);
	
	if (config->path_index >= config->path_steps)
		return ;

	next_step = config->path_to_player[config->path_index];

	// check if it's in the middle of the next cell
	if (map_pos.x == floorf(next_step.x)
	&& map_pos.y == floorf(next_step.y))
	{
		config->path_index++;
		if (config->path_index >= config->path_steps)
			return ;
		next_step = config->path_to_player[config->path_index];
	}

	// move sprite
	if (next_step.x > map_pos.x || config->sprite_pos.x - next_step.x * UNIT < UNIT / 2)
		config->sprite_pos.x += mov_speed;
	if ((next_step.x < map_pos.x
	|| (next_step.x * UNIT - config->sprite_pos.x) < (UNIT / 2)) 
	&& !(config->sprite_pos.x - next_step.x * UNIT < UNIT / 2))
		config->sprite_pos.x -= mov_speed;
	if (next_step.y > map_pos.y || (config->sprite_pos.y - next_step.y * UNIT) < UNIT / 2)
		config->sprite_pos.y += mov_speed;
	if ((next_step.y < map_pos.y 
	|| (next_step.y * UNIT - config->sprite_pos.y) < (UNIT / 2))
	&& !((config->sprite_pos.y - next_step.y * UNIT) < UNIT / 2))
		config->sprite_pos.y -= mov_speed;
	
}
