/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/08 14:06:20 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	rotate(t_config *config, float rot_speed)
{
	if (config->rotate_left)
	{
		config->viewAngle = normalize_angle(config->viewAngle - rot_speed);
		config->dirY = sin(config->viewAngle * DEG_TO_RAD);
		config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	}
	if (config->rotate_right)
	{
		config->viewAngle = normalize_angle(config->viewAngle + rot_speed);
		config->dirY = sin(config->viewAngle * DEG_TO_RAD);
		config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	}
}

void	reset_game(t_config *config)
{
	int			i;
	t_vector	map_pos;

	config->lost = 0;
	config->won = 0;
	config->collectibles_left = config->collectibles_tmp;
	i = 0;
	while (i < config->sprite_count)
	{
		config->sprites[i].visible = 1;
		config->sprites[i].x = config->sprites[i].initial_x;
		config->sprites[i].y = config->sprites[i].initial_y;
		map_pos.x = floorf(config->sprites[i].x / UNIT);
		map_pos.y = floorf(config->sprites[i].y / UNIT);
		config->map[(int)map_pos.y][(int)map_pos.x]
			= config->sprites[i].type + 2;
		i++;
	}
	config->xPos = config->initial_player_x;
	config->yPos = config->initial_player_y;
	config->viewAngle = get_view_angle(config);
	assign_paths(config);
}

int	enemy_in_door(t_config *config)
{
	t_vector	enemy_pos;
	int			i;

	i = 0;
	while (i < config->sprite_count)
	{
		if (config->sprites[i].type == ENEMY)
		{
			enemy_pos.x = floorf(config->sprites[i].x / UNIT);
			enemy_pos.y = floorf(config->sprites[i].y / UNIT);
			if (enemy_pos.x == config->visible_door.x
				&& enemy_pos.y == config->visible_door.y)
				return (1);
		}
		i++;
	}
	return (0);
}

void	loop_hook(t_config *config)
{
	if (config->fail)
	{
		free_config(config);
		exit(EXIT_FAILURE);
	}
	if (config->is_starting)
	{
		display_full(config, config->entry_texture);
		return ;
	}
	if (config->lost)
	{
		display_full(config, config->loss_texture);
		return ;
	}
	if (config->won)
	{
		display_full(config, config->win_texture);
		return ;
	}
	config->visible_door = (t_vector){.x = -1, .y = -1};
	move_player(config);
	redraw_image(config);
}
