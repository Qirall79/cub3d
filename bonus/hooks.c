/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/21 15:48:23 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float normalize_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return angle;
}

int is_wall_v(float newX, float newY, t_config *config)
{
	
	if (config->map[(int)(config->yPos + newY) / UNIT][(int)(config->xPos) / UNIT] == 1
	|| config->map[(int)(config->yPos + newY) / UNIT][(int)(config->xPos) / UNIT] == 4)
		return 1;
	return 0;
}
int is_wall_h(float newX, float newY, t_config *config)
{
	if (config->map[(int)(config->yPos) / UNIT][(int)(config->xPos + newX) / UNIT] == 1
	|| config->map[(int)(config->yPos) / UNIT][(int)(config->xPos + newX) / UNIT] == 4)
		return 1;
	return 0;
}

void check_collection(t_config *config)
{
	t_vector map_pos;
	t_vector collectible_pos;
	int i;

	map_pos.x = floorf(config->xPos / UNIT);
	map_pos.y = floorf(config->yPos / UNIT);

	if (config->map[(int)map_pos.y][(int)map_pos.x] == 3)
	{
		config->map[(int)map_pos.y][(int)map_pos.x] = 0;
		config->collectibles_left--;
		i = 0;
		while (i < config->sprite_count)
		{
			collectible_pos.x = floorf(config->sprites[i].x / UNIT);
			collectible_pos.y = floorf(config->sprites[i].y / UNIT);
			
			if (collectible_pos.x == map_pos.x
			&& collectible_pos.y == map_pos.y)
			{
				config->sprites[i].visible = 0;
				break ;
			}

			i++;
		}
	}

	if (config->collectibles_left <= 0)
		config->won = 1;
}

void move_player(t_config *config)
{
	float newX;
	float newY;
	float mov_speed = config->mlx->delta_time * UNIT * 3.5;
	float rot_speed = config->mlx->delta_time * 100.0;

	// camera rotation
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

	// player movement
	if (config->move_left)
	{
		newY = -sin(normalize_angle(config->viewAngle + 90) * DEG_TO_RAD) * mov_speed;
		newX = -cos(normalize_angle(config->viewAngle + 90) * DEG_TO_RAD) * mov_speed;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
			config->xPos += newX;
		else if (is_wall_h(newX, newY, config))
			config->yPos += newY;
		else
		{
			config->xPos += newX;
			config->yPos += newY;
		}
	}
	if (config->move_right)
	{
		newY = sin(normalize_angle(config->viewAngle + 90) * DEG_TO_RAD) * mov_speed;
		newX = cos(normalize_angle(config->viewAngle + 90) * DEG_TO_RAD) * mov_speed;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
			config->xPos += newX;
		else if (is_wall_h(newX, newY, config))
			config->yPos += newY;
		else
		{
			config->xPos += newX;
			config->yPos += newY;
		}
	}
	if (config->move_forward)
	{
		newY = sin(config->viewAngle * DEG_TO_RAD) * mov_speed;
		newX = cos(config->viewAngle * DEG_TO_RAD) * mov_speed;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
			config->xPos += newX;
		else if (is_wall_h(newX, newY, config))
			config->yPos += newY;
		else
		{
			config->xPos += newX;
			config->yPos += newY;
		}
	}
	if (config->move_backward)
	{
		newY = -sin(config->viewAngle * DEG_TO_RAD) * mov_speed;
		newX = -cos(config->viewAngle * DEG_TO_RAD) * mov_speed;

		if (is_wall_v(newX, newY, config) && is_wall_h(newX, newY, config))
			return ;
		if (is_wall_v(newX, newY, config))
			config->xPos += newX;
		else if (is_wall_h(newX, newY, config))
			config->yPos += newY;
		else
		{
			config->xPos += newX;
			config->yPos += newY;
		}
	}
	
	check_collection(config);

	if (config->move_backward || config->move_forward
	|| config->move_right || config->move_left)
		assign_paths(config);
}

void reset_game(t_config *config)
{
	int i;
	t_vector map_pos;

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
		config->map[(int)map_pos.y][(int)map_pos.x] = config->sprites[i].type + 2;
		i++;
	}
	config->xPos = config->initial_player_x;
	config->yPos = config->initial_player_y;
	config->viewAngle = 180.0;
	assign_paths(config);
}

int enemy_in_door(t_config *config)
{
	t_vector enemy_pos;
	int i;

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

void set_movement_params(mlx_key_data_t keydata, t_config *config)
{
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		config->move_forward = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		config->move_forward = 0;
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		config->move_backward = 1;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		config->move_backward = 0;
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		config->move_right = 1;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		config->move_right = 0;
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		config->move_left = 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		config->move_left = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
		config->rotate_right = 1;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		config->rotate_right = 0;
	if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
		config->rotate_left = 1;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		config->rotate_left = 0;
	if (keydata.key == MLX_KEY_SPACE && config->is_starting)
		config->is_starting = 0;
	if (keydata.key == MLX_KEY_ENTER && (config->lost || config->won))
		reset_game(config);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS && config->visible_door.x != -1)
	{
		if (!enemy_in_door(config))
		{
			if (config->map[(int)config->visible_door.y][(int)config->visible_door.x] == 4)
				config->map[(int)config->visible_door.y][(int)config->visible_door.x] = 6;
			else
				config->map[(int)config->visible_door.y][(int)config->visible_door.x] = 4;
			assign_paths(config);
		}
	}
}

void display_full(t_config *config, int **texture)
{
	int i;
	int j;

	i = 0;
	while (i < config->height)
	{
		j = 0;
		while (j < config->width)
		{
			mlx_put_pixel(config->img, j, i, texture[i][j]);
			j++;
		}
		i++;
	}
}

void loop_hook(t_config *config)
{
	t_vector door;

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

	config->visible_door = (t_vector) {.x = -1, .y = -1};
	move_player(config);
	redraw_image(config);
}

void handle_mouse(double xpos, double ypos, t_config *config)
{
	double increment;
	
	increment = (xpos - config->width / 2.0) / 8;

	config->viewAngle = normalize_angle(config->viewAngle + increment);
	config->dirY = sin(config->viewAngle * DEG_TO_RAD);
	config->dirX = cos(config->viewAngle * DEG_TO_RAD);

	mlx_set_mouse_pos(config->mlx, config->width / 2.0, config->height / 2.0);
}