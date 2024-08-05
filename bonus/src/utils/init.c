/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:10:37 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/05 23:04:29 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_dimensions(t_config *config)
{
	config->width = WIDTH;
	config->height = HEIGHT;
	// config->map_width = MAP_WIDTH;
	// config->map_height = MAP_HEIGHT;
}

void	init_screens(t_config *config)
{
	t_dimensions	window_d;

	window_d = (t_dimensions){.height = config->height, .width = config->width};
	config->entry_texture
		= generate_texture("./textures/start_screen.png", config, window_d);
	config->win_texture
		= generate_texture("./textures/win_screen.png", config, window_d);
	config->loss_texture
		= generate_texture("./textures/loss_screen.png", config, window_d);
}

void	init_sprites_textures(t_config *config)
{
	t_dimensions	wall_d;

	wall_d = (t_dimensions){.height = UNIT, .width = UNIT};
	config->sprite_count = count_sprites(config);
	config->collectibles_left = 0;
	config->sprites
		= (t_sprite *)malloc(config->sprite_count * sizeof(t_sprite));
	if (!config->sprites)
		return (set_failure(config));
	config->texture_east
		= generate_texture("./textures/chrollo_portrait.png", config, wall_d);
	config->texture_west
		= generate_texture("./textures/hisoka_portrait.png", config, wall_d);
	config->texture_north
		= generate_texture("./textures/killua.png", config, wall_d);
	config->texture_south
		= generate_texture("./textures/meruem.png", config, wall_d);
	config->enemy_texture
		= generate_texture("./textures/monster.png", config, wall_d);
	config->collectible_texture
		= generate_texture("./textures/banana.png", config, wall_d);
	config->door_texture
		= generate_texture("./textures/door.png", config, wall_d);
	init_screens(config);
}

void	init_config(t_config *config)
{
	config->fovAngle = 60.0;
	config->viewAngle = 180.0;
	config->dirY = sin(config->viewAngle * DEG_TO_RAD);
	config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	config->rays = (int *) malloc(config->width * sizeof(int));
	if (!config->rays)
		set_failure(config);
	config->sprite_offset = 0;
	config->flying_up = 0;
	config->path_index = 0;
	config->lost = 0;
	config->won = 0;
	config->is_starting = 1;
	config->initial_player_x = config->xPos;
	config->initial_player_y = config->yPos;
	config->visible_door = (t_vector){.x = -1, .y = -1};
	config->move_forward = 0;
	config->move_backward = 0;
	config->move_right = 0;
	config->move_left = 0;
	config->rotate_left = 0;
	config->rotate_right = 0;
	assign_paths(config);
}

void	init_game(t_config *config)
{
	/*---- parsing start ----*/
	// int	world_map[MAP_HEIGHT][MAP_WIDTH] = {
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 1, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	// {1, 1, 1, 1, 1, 1, 1, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	// {1, 1, 0, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 1},
	// {1, 1, 0, 1, 0, 0, 5, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
	// {1, 1, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	// {1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	// {1, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	// };
	set_dimensions(config);
	// copy_map(config, world_map);
	/*---- parsing end ----*/
	config->fail = 0;
	init_sprites_textures(config);
	if (config->fail)
		return ;
	set_pos(config);
	config->collectibles_tmp = config->collectibles_left;
	config->mlx = mlx_init(config->width, config->height, "Cub3D", 0);
	if (!config->mlx)
		printf("ERROR initializing MLX\n");
	config->img = mlx_new_image(config->mlx, config->width, config->height);
	if (!config->img
		|| (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		printf("ERROR initializing MLX image\n");
	mlx_set_cursor_mode(config->mlx, MLX_MOUSE_HIDDEN);
	init_config(config);
}
