/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/14 19:39:42 by wbelfatm         ###   ########.fr       */
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
				config->yPos = i;
				config->xPos = j;
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

uint32_t abgr_to_rgba(uint32_t abgr_color) {
  // Extract individual color channels with bit shifting and masking
  uint8_t alpha = (abgr_color >> 24) & 0xFF;
  uint8_t blue = (abgr_color >> 16) & 0xFF;
  uint8_t green = (abgr_color >> 8) & 0xFF;
  uint8_t red = abgr_color & 0xFF;

  if (!alpha)
	alpha = 127;

  // Reassemble color in RGBA format by shifting and combining
  return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

void init_config(t_config *config)
{
	int worldMap[MAP_WIDTH][MAP_HEIGHT]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	
	copy_map(config, worldMap);
	set_pos(config);
	config->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	if (!config->mlx)
		printf("ERROR initializing MLX\n");
	config->img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		printf("ERROR initializing MLX image\n");
	config->xOffset = 0;
	config->yOffset = 0;
	config->fovAngle = 60.0;
	config->viewAngle = 90.0;
	config->dirY = sin(config->viewAngle * DEG_TO_RAD) * WIDTH;
	config->dirX = cos(config->viewAngle * DEG_TO_RAD) * WIDTH;
	config->initialX = config->xPos;
	config->initialY = config->yPos;
	config->xPos = config->initialX * UNIT + (UNIT - 10) / 2;
	config->yPos = config->initialY * UNIT + (UNIT - 10) / 2;

	// init keys
	config->move_forward = 0;
	config->move_backward = 0;
	config->move_right = 0;
	config->move_left = 0;
	config->rotate_left = 0;
	config->rotate_right = 0;


	// load mlx png
	mlx_texture_t *tex = mlx_load_png("./textures/gonn.png");
	if (!tex)
		(printf("FAIL\n"), exit(1));

	// textures
	int **arr = (int **)malloc(tex->height * sizeof(int *));
    for (int i = 0; i < tex->height; i++) {
        arr[i] = (int *)malloc(tex->width * sizeof(int));
    }
    int *pixels = (int *) tex->pixels;
	for (int i = 0; i < tex->height; i++) {
        for (int j = 0; j < tex->width; j++)
		{
			arr[i][j] = abgr_to_rgba(pixels[i * tex->width + j]);
		}
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

