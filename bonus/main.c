/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/21 11:59:51 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count_sprites(t_config *config)
{
	int count;
	int i;
	int j;

	count = 0;
	i = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			if (config->map[i][j] == 2 || config->map[i][j] == 3)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void set_pos(t_config *config)
{
	int i = 0;
	int j = 0;
	int sprites_index = 0;

	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			if (config->map[i][j] == 5)
			{
				config->yPos = i * UNIT + (UNIT - 10) / 2;
				config->xPos = j * UNIT + (UNIT - 10) / 2;
			}
			if (config->map[i][j] == 2 || config->map[i][j] == 3)
			{
				config->sprite_pos.y = i * UNIT + UNIT / 2;
				config->sprite_pos.x = j * UNIT + UNIT / 2;
				config->sprites[sprites_index] = (t_sprite){
					.x = config->sprite_pos.x,
					.y = config->sprite_pos.y,
					.initial_x = config->sprite_pos.x,
					.initial_y = config->sprite_pos.y,
					.type = config->map[i][j] - 2,
					.visible = 1,
					.texture = config->enemy_texture
				};
				if (config->sprites[sprites_index].type == COLLECTIBLE)
				{
					config->sprites[sprites_index].texture = config->collectible_texture;
					config->collectibles_left++;
				}
					
				sprites_index++;
			}
			j++;
		}
		i++;
	}
}

void copy_map(t_config *config, int map[MAP_HEIGHT][MAP_WIDTH])
{
	int i = 0;
	int j = 0;

	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			config->map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}

uint32_t abgr_to_rgba(uint32_t abgr_color) {
  uint8_t alpha = (abgr_color >> 24) & 0xFF;
  uint8_t blue = (abgr_color >> 16) & 0xFF;
  uint8_t green = (abgr_color >> 8) & 0xFF;
  uint8_t red = abgr_color & 0xFF;

  return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

int **generate_texture(char *path, t_config *config, int height, int width)
{
	int **arr;
	mlx_texture_t *tex;
	int *pixels;
	t_vector step;
	t_vector iter;
	int x;
	int y;

	tex = mlx_load_png(path);
	if (!tex)
		(printf("FAIL\n"), exit(1));
	config->tex = tex;
	arr = (int **)malloc(height * sizeof(int *));
	iter.y = 0;
    while (iter.y < height) {
        arr[(int)iter.y] = (int *)malloc(width * sizeof(int));
		iter.y++;
    }
    pixels = (int *) tex->pixels;
	step.x = tex->width / (float)width;
	step.y = tex->height / (float)height;
	iter.x = 0;
	y = 0;
	while (y < height) {
		iter.y = 0;
		x = 0;
        while (x < width)
		{
			arr[y][x] = abgr_to_rgba(pixels[(int)floorf(iter.x) * tex->width + (int)floorf(iter.y)]);
			iter.y += step.x;
			x++;
		}
		iter.x += step.y;
		y++;
	}
	return (arr);
}

void assign_paths(t_config *config)
{
	int i;

	i = 0;
	while (i < config->sprite_count)
	{
		if (config->sprites[i].type == ENEMY)
			solve_a_star_sprite(config, &config->sprites[i]);
		i++;
	}
}

void init_config(t_config *config)
{

	/*---- parsing start ----*/

	int worldMap[MAP_HEIGHT][MAP_WIDTH]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,3,0,1,0,0,0,0,0,0,3,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,1,1,1,1,1,6,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,0,1,3,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,0,1,0,0,5,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
	{1,1,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,3,1},
	{1,1,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1},
	{1,1,0,0,0,0,3,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	config->width = WIDTH;
	config->height = HEIGHT;
	config->map_width = MAP_WIDTH;
	config->map_height = MAP_HEIGHT;
	copy_map(config, worldMap);
	
	/*---- parsing end ----*/
	
	// initialize sprites
	config->sprite_count = count_sprites(config);
	config->collectibles_left = 0;
	config->sprites = (t_sprite *) malloc(config->sprite_count * sizeof(t_sprite));

	// load textures
	config->texture_east = generate_texture("./textures/wall_1.png", config, UNIT, UNIT);
	config->texture_west = generate_texture("./textures/wall_3.png", config, UNIT, UNIT);
	config->texture_north = generate_texture("./textures/wall_2.png", config, UNIT, UNIT);
	config->texture_south = generate_texture("./textures/wall_4.png", config, UNIT, UNIT);
	config->enemy_texture = generate_texture("./textures/monster.png", config, UNIT, UNIT);
	config->collectible_texture = generate_texture("./textures/banana.png", config, UNIT, UNIT);
	config->entry_texture = generate_texture("./textures/start_screen.png", config, config->height, config->width);
	config->win_texture = generate_texture("./textures/win_screen.png", config, config->height, config->width);
	config->loss_texture = generate_texture("./textures/loss_screen.png", config, config->height, config->width);
	config->door_texture = generate_texture("./textures/door.png", config, UNIT, UNIT);

	set_pos(config);
	config->collectibles_tmp = config->collectibles_left;

	config->mlx = mlx_init(config->width, config->height, "Cub3D", 0);
	if (!config->mlx)
		printf("ERROR initializing MLX\n");
	config->img = mlx_new_image(config->mlx, config->width, config->height);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		printf("ERROR initializing MLX image\n");
	config->fovAngle = 60.0;
	config->viewAngle = 180.0;
	config->dirY = sin(config->viewAngle * DEG_TO_RAD);
	config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	config->rays = (int *) malloc(config->width * sizeof(int));
	config->sprite_offset = 0;
	config->flying_up = 0;
	config->path_to_player = NULL;
	config->path_index = 0;
	config->lost = 0;
	config->won = 0;
	config->is_starting = 1;
	config->initial_player_x = config->xPos;
	config->initial_player_y = config->yPos;
	config->visible_door = (t_vector) {.x = -1, .y = -1};

	// init keys
	config->move_forward = 0;
	config->move_backward = 0;
	config->move_right = 0;
	config->move_left = 0;
	config->rotate_left = 0;
	config->rotate_right = 0;
	
	// A star
	assign_paths(config);
}

int main(void)
{
	t_config config;

	init_config(&config);
	draw_map(&config);

	// hooks
	mlx_key_hook(config.mlx, (mlx_keyfunc) set_movement_params, &config);
	mlx_loop_hook(config.mlx, (void *) loop_hook, &config);

	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
	return (EXIT_SUCCESS);
}
