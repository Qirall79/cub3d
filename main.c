/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/19 14:49:40 by wbelfatm         ###   ########.fr       */
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
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
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

	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
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
					.type = config->map[i][j] - 2,
					.visible = 1,
					.texture = config->enemy_texture
				};
				if (config->sprites[sprites_index].type == COLLECTIBLE)
					config->sprites[sprites_index].texture = config->collectible_texture;
					
				sprites_index++;
			}
			j++;
		}
		i++;
	}
}

void copy_map(t_config *config, int map[MAP_WIDTH][MAP_HEIGHT])
{
	int i = 0;
	int j = 0;

	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
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

int **generate_texture(char *path, t_config *config)
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
	arr = (int **)malloc(UNIT * sizeof(int *));
	iter.y = 0;
    while (iter.y < UNIT) {
        arr[(int)iter.y] = (int *)malloc(UNIT * sizeof(int));
		iter.y++;
    }
    pixels = (int *) tex->pixels;
	step.x = tex->width / (float)UNIT;
	step.y = tex->height / (float)UNIT;
	iter.x = 0;
	y = 0;
	while (y < UNIT) {
		iter.y = 0;
		x = 0;
        while (x < UNIT)
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

int **generate_enemy(char *path, t_config *config)
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
	arr = (int **)malloc(ENEMY_SIZE * sizeof(int *));
	iter.y = 0;
    while (iter.y < ENEMY_SIZE) {
        arr[(int)iter.y] = (int *)malloc(ENEMY_SIZE * sizeof(int));
		iter.y++;
    }
    pixels = (int *) tex->pixels;
	step.x = tex->width / (float)ENEMY_SIZE;
	step.y = tex->height / (float)ENEMY_SIZE;
	iter.x = 0;
	y = 0;
	while (y < ENEMY_SIZE) {
		iter.y = 0;
		x = 0;
        while (x < ENEMY_SIZE)
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
	int worldMap[MAP_WIDTH][MAP_HEIGHT]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,0,1,3,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,0,1,0,0,5,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
	{1,1,3,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1},
	{1,1,0,2,0,0,3,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	copy_map(config, worldMap);
	config->sprite_count = count_sprites(config);
	config->sprites = (t_sprite *) malloc(config->sprite_count * sizeof(t_sprite));

	// load textures
	config->texture_east = generate_texture("./textures/wall_1.png", config);
	config->texture_west = generate_texture("./textures/wall_3.png", config);
	config->texture_north = generate_texture("./textures/wall_2.png", config);
	config->texture_south = generate_texture("./textures/wall_4.png", config);
	config->enemy_texture = generate_enemy("./textures/monster.png", config);
	config->collectible_texture = generate_texture("./textures/banana.png", config);

	set_pos(config);
	config->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	if (!config->mlx)
		printf("ERROR initializing MLX\n");
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		printf("ERROR initializing MLX image\n");
	config->fovAngle = 60.0;
	config->viewAngle = 180.0;
	config->dirY = sin(config->viewAngle * DEG_TO_RAD);
	config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	config->rays = (int *) malloc(WIDTH * sizeof(int));
	config->sprite_offset = 0;
	config->flying_up = 0;
	config->path_to_player = NULL;
	config->path_index = 0;

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

void draw_texture(t_config *config)
{
	int i = 0;
	int j;

	while (i < UNIT && i < HEIGHT)
	{
		j = 0;
		while (j < UNIT && j < WIDTH)
		{
			if ((char)config->texture[i][j] != 0)
				mlx_put_pixel(config->img, j, i, config->texture[i][j]);
			j++;
		}
		i++;
		
	}
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

