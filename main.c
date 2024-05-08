/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/08 17:18:27 by wbelfatm         ###   ########.fr       */
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
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	config->xOffset = 0;
	config->yOffset = 0;
	config->fovAngle = 60.0;
	config->viewAngle = 180.0;
	config->dirY = sin(config->viewAngle * M_PI / 180.0) * WIDTH;
	config->dirX = cos(config->viewAngle * M_PI / 180.0) * WIDTH;
	config->initialX = config->xPos;
	config->initialY = config->yPos;
	config->xPos = config->initialX * unit + (unit - 10) / 2;
	config->yPos = config->initialY * unit + (unit - 10) / 2;

	// init keys
	config->move_forward = 0;
	config->move_backward = 0;
	config->move_right = 0;
	config->move_left = 0;
	config->rotate_left = 0;
	config->rotate_right = 0;
}

int main(void)
{
	t_config config;

	init_config(&config);
	draw_map(&config);

	// hooks
	mlx_key_hook(config.mlx, (mlx_keyfunc) set_movement_params, &config);
	mlx_loop_hook(config.mlx, loop_hook, &config);

	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
	return (EXIT_SUCCESS);
}

