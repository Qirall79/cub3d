/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/22 12:47:02 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_sprites(t_config *config)
{
	int	count;
	int	i;
	int	j;

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

void	set_sprites_pos(t_config *config, int index, int i, int j)
{
	config->sprite_pos.y = i * UNIT + UNIT / 2;
	config->sprite_pos.x = j * UNIT + UNIT / 2;
	config->sprites[index] = (t_sprite){
		.x = config->sprite_pos.x,
		.y = config->sprite_pos.y,
		.initial_x = config->sprite_pos.x,
		.initial_y = config->sprite_pos.y,
		.type = config->map[i][j] - 2,
		.visible = 1,
		.texture = config->enemy_texture
	};
	if (config->sprites[index].type == COLLECTIBLE)
	{
		config->sprites[index].texture = config->collectible_texture;
		config->collectibles_left++;
	}
}

void	set_pos(t_config *config)
{
	int	i;
	int	j;
	int	sprites_index;

	i = 0;
	sprites_index = 0;
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
				set_sprites_pos(config, sprites_index, i, j);
				sprites_index++;
			}
			j++;
		}
		i++;
	}
}

void	copy_map(t_config *config, int map[MAP_HEIGHT][MAP_WIDTH])
{
	int	i;
	int	j;

	i = 0;
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

uint32_t	abgr_to_rgba(uint32_t abgr_color)
{
	uint8_t	alpha;
	uint8_t	blue;
	uint8_t	green;
	uint8_t	red;

	alpha = (abgr_color >> 24) & 0xFF;
	blue = (abgr_color >> 16) & 0xFF;
	green = (abgr_color >> 8) & 0xFF;
	red = abgr_color & 0xFF;
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

int	**allocate_texture(t_config *config, t_dimensions d)
{
	int	**arr;
	int	y;

	arr = (int **)malloc(d.height * sizeof(int *));
	y = 0;
	while (y < d.height)
	{
		arr[y] = (int *)malloc(d.width * sizeof(int));
		y++;
	}
	return (arr);
}

int	get_color_index(mlx_texture_t *tex, int x, int y, t_dimensions d)
{
	int	i;
	int	j;

	i = (int)floorf(y * (tex->height / (float)d.height));
	j = (int)floorf(x * (tex->width / (float)d.width));
	return (i * tex->width + j);
}

void	load_texture(t_config *config, char *path)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(path);
	if (!tex)
		(printf("FAIL\n"), exit(EXIT_FAILURE));
	config->tex = tex;
}

int	**generate_texture(char *path, t_config *config, t_dimensions d)
{
	int				**arr;
	mlx_texture_t	*tex;
	int				*pixels;
	int				x;
	int				y;

	load_texture(config, path);
	arr = allocate_texture(config, d);
	if (!arr)
		return (NULL);
	pixels = (int *) config->tex->pixels;
	y = 0;
	while (y < d.height)
	{
		x = 0;
		while (x < d.width)
		{
			arr[y][x] = abgr_to_rgba(
					pixels[get_color_index(config->tex, x, y, d)]);
			x++;
		}
		y++;
	}
	return (arr);
}

void	assign_paths(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->sprite_count)
	{
		if (config->sprites[i].type == ENEMY)
			solve_a_star(config, &config->sprites[i]);
		i++;
	}
}

void	set_dimensions(t_config *config)
{
	config->width = WIDTH;
	config->height = HEIGHT;
	config->map_width = MAP_WIDTH;
	config->map_height = MAP_HEIGHT;
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
	config->texture_east
		= generate_texture("./textures/wall_1.png", config, wall_d);
	config->texture_west
		= generate_texture("./textures/wall_3.png", config, wall_d);
	config->texture_north
		= generate_texture("./textures/wall_2.png", config, wall_d);
	config->texture_south
		= generate_texture("./textures/wall_4.png", config, wall_d);
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
	config->sprite_offset = 0;
	config->flying_up = 0;
	config->path_to_player = NULL;
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

void init_game(t_config *config)
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
	{1,1,0,1,3,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,3,1},
	{1,1,0,1,0,0,5,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
	{1,1,0,4,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1},
	{1,1,0,0,0,0,3,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	set_dimensions(config);
	copy_map(config, worldMap);
	
	/*---- parsing end ----*/
	init_sprites_textures(config);
	set_pos(config);
	config->collectibles_tmp = config->collectibles_left;

	config->mlx = mlx_init(config->width, config->height, "Cub3D", 0);
	if (!config->mlx)
		printf("ERROR initializing MLX\n");
	config->img = mlx_new_image(config->mlx, config->width, config->height);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		printf("ERROR initializing MLX image\n");
	mlx_set_cursor_mode(config->mlx, MLX_MOUSE_HIDDEN);
	init_config(config);
}

int main(void)
{
	t_config config;

	init_game(&config);
	draw_map(&config);

	// hooks
	mlx_key_hook(config.mlx, (mlx_keyfunc) set_movement_params, &config);
	mlx_cursor_hook(config.mlx, (mlx_cursorfunc) handle_mouse, &config);
	mlx_loop_hook(config.mlx, (void *) loop_hook, &config);

	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
	return (EXIT_SUCCESS);
}
