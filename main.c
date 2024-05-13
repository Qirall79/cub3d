/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/12 11:24:33 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_pos(t_config *config)
{
	int i = 0;
	int j = 0;

	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (config->map[i][j] == 5)
			{
				config->player.x = j;
				config->player.y = i;
				return ;
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

void init_config(t_config *config)
{
	int worldMap[MAP_WIDTH][MAP_HEIGHT]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,4,0,0,0,0,5,0,4,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	int unit = WIDTH / MAP_WIDTH;

	copy_map(config, worldMap);
	set_pos(config);
	config->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	if (!config->mlx)
		printf("ERROR initializing MLX\n");
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		printf("ERROR initializing MLX image\n");
	config->fovAngle = 60.0;
	config->viewAngle = 90.0;
	config->dir.y = 0;
	config->dir.x = 1;
	config->plane.x = 0;
	config->plane.y = 0.66;

	// init keys
	config->move_forward = 0;
	config->move_backward = 0;
	config->move_right = 0;
	config->move_left = 0;
	config->rotate_left = 0;
	config->rotate_right = 0;

	// textures
	mlx_texture_t *tex = mlx_load_png("./textures/bluestone.png");
	mlx_image_t *img = mlx_texture_to_image(config->mlx, tex);

	int **arr = (int **)malloc(tex->height * sizeof(int *));
    for (int i = 0; i < tex->height; i++) {
        arr[i] = (int *)malloc(tex->width * sizeof(int));
    }
	
	int y = 0;
	int x = 0;
	while ( y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			arr[y][x] = tex->pixels[y * tex->width + x];
			x++;
		}
		y++;
	}
	config->texture = arr;
	config->tex = tex;
}

void draw_texture(t_config *config)
{
	int i = 0;
	int j;

	while (i < config->tex->height && i < HEIGHT)
	{
		j = 0;
		while (j < config->tex->width && j < WIDTH)
		{
			mlx_put_pixel(config->img, j, i, config->texture[i][j] * 0xFFFFFFFF);
			j++;
		}
		i++;
		
	}
}

int main(void)
{
	t_config config;

	init_config(&config);

	draw_texture(&config);

	// draw_map(&config);

	// hooks
	mlx_key_hook(config.mlx, (mlx_keyfunc) set_movement_params, &config);
	// mlx_loop_hook(config.mlx, (void *) loop_hook, &config);

	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
	return (EXIT_SUCCESS);
}

