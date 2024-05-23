/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/23 11:55:58 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	if (angle > 360)
		return (angle - 360);
	if (angle < 0)
		return (angle + 360);
	return (angle);
}

int	is_wall_v(float newX, float newY, t_config *config)
{
	int	x;
	int	y;

	y = (int)(config->yPos + newY) / UNIT;
	x = (int)(config->xPos) / UNIT;
	if (config->map[y][x] == 1
	|| config->map[y][x] == 4)
		return (1);
	return (0);
}

int	is_wall_h(float newX, float newY, t_config *config)
{
	int	x;
	int	y;

	x = (int)(config->xPos + newX) / UNIT;
	y = (int)(config->yPos) / UNIT;
	if (config->map[y][x] == 1
	|| config->map[y][x] == 4)
		return (1);
	return (0);
}

void	check_collection(t_config *config)
{
	t_vector	map_pos;
	t_vector	collectible_pos;
	int			i;

	map_pos.x = floorf(config->xPos / UNIT);
	map_pos.y = floorf(config->yPos / UNIT);
	if (config->map[(int)map_pos.y][(int)map_pos.x] == 3)
	{
		config->map[(int)map_pos.y][(int)map_pos.x] = 0;
		config->collectibles_left--;
		i = -1;
		while (++i < config->sprite_count)
		{
			collectible_pos.x = floorf(config->sprites[i].x / UNIT);
			collectible_pos.y = floorf(config->sprites[i].y / UNIT);
			if (collectible_pos.x == map_pos.x
				&& collectible_pos.y == map_pos.y)
			{
				config->sprites[i].visible = 0;
				break ;
			}
		}
	}
	if (config->collectibles_left <= 0)
		config->won = 1;
}

void	move_forward(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = sin(config->viewAngle * DEG_TO_RAD) * mov_speed;
	new_x = cos(config->viewAngle * DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

void	move_backward(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = -sin(config->viewAngle * DEG_TO_RAD) * mov_speed;
	new_x = -cos(config->viewAngle * DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

void	move_right(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = sin(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	new_x = cos(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

void	move_left(t_config *config, float mov_speed)
{
	float	new_x;
	float	new_y;

	new_y = -sin(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	new_x = -cos(normalize_angle(config->viewAngle + 90)
			* DEG_TO_RAD) * mov_speed;
	if (is_wall_v(new_x, new_y, config) && is_wall_h(new_x, new_y, config))
		return ;
	if (is_wall_v(new_x, new_y, config))
		config->xPos += new_x;
	else if (is_wall_h(new_x, new_y, config))
		config->yPos += new_y;
	else
	{
		config->xPos += new_x;
		config->yPos += new_y;
	}
}

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

void	move_player(t_config *config)
{
	float	mov_speed;
	float	rot_speed;

	mov_speed = config->mlx->delta_time * UNIT * 3.5;
	rot_speed = config->mlx->delta_time * 100.0;
	rotate(config, rot_speed);
	if (config->move_left)
		move_left(config, mov_speed);
	if (config->move_right)
		move_right(config, mov_speed);
	if (config->move_forward)
		move_forward(config, mov_speed);
	if (config->move_backward)
		move_backward(config, mov_speed);
	check_collection(config);
	if (config->move_backward || config->move_forward
		|| config->move_right || config->move_left)
		assign_paths(config);
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
	config->viewAngle = 180.0;
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

void	set_movement_params(mlx_key_data_t keydata, t_config *config)
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
}

void	handle_click(mlx_key_data_t keydata, t_config *config)
{
	int	x;
	int	y;

	set_movement_params(keydata, config);
	if (keydata.key == MLX_KEY_SPACE && config->is_starting)
		config->is_starting = 0;
	if (keydata.key == MLX_KEY_ENTER && (config->lost || config->won))
		reset_game(config);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS
		&& config->visible_door.x != -1)
	{
		if (!enemy_in_door(config))
		{
			x = (int)config->visible_door.x;
			y = (int)config->visible_door.y;
			if (config->map[y][x] == 4)
				config->map[y][x] = 6;
			else
				config->map[y][x] = 4;
			assign_paths(config);
		}
	}
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(config->mlx);
		free_config(config);
		exit(EXIT_SUCCESS);
	}
}

void	display_full(t_config *config, int **texture)
{
	int	i;
	int	j;

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

void	loop_hook(t_config *config)
{
	t_vector	door;

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

void	handle_mouse(double xpos, double ypos, t_config *config)
{
	double	increment;

	increment = (xpos - config->width / 2.0) / 8;
	config->viewAngle = normalize_angle(config->viewAngle + increment);
	config->dirY = sin(config->viewAngle * DEG_TO_RAD);
	config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	mlx_set_mouse_pos(config->mlx, config->width / 2.0, config->height / 2.0);
}
