/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:10:37 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/12 18:37:35 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_sprites_textures(t_config *config)
{
	t_dimensions	wall_d;

	wall_d = (t_dimensions){.height = UNIT, .width = UNIT};
	config->texture_east
		= generate_texture(config->path_e, config, wall_d);
	config->texture_west
		= generate_texture(config->path_w, config, wall_d);
	config->texture_north
		= generate_texture(config->path_n, config, wall_d);
	config->texture_south
		= generate_texture(config->path_s, config, wall_d);
}

float	get_view_angle(t_config *config)
{
	if (config->orientation == 'N')
		return (270.0);
	if (config->orientation == 'W')
		return (180.0);
	if (config->orientation == 'S')
		return (90.0);
	return (0.0);
}

void	init_config(t_config *config)
{
	config->fov_angle = 60.0;
	config->view_angle = get_view_angle(config);
	config->dir_y = sin(config->view_angle * DEG_TO_RAD);
	config->dir_x = cos(config->view_angle * DEG_TO_RAD);
	config->initial_player_x = config->x_pos;
	config->initial_player_y = config->y_pos;
	config->move_forward = 0;
	config->move_backward = 0;
	config->move_right = 0;
	config->move_left = 0;
	config->rotate_left = 0;
	config->rotate_right = 0;
}

void	init_game(t_config *config, t_tools *items)
{
	config->fail = 0;
	init_map(config, items);
	// if (config->fail)
	// 	return ;
	// config->width = WIDTH;
	// config->height = HEIGHT;
	// init_sprites_textures(config);
	// if (config->fail)
	// 	return ;
	// set_pos(config);
	// config->mlx = mlx_init(config->width, config->height, "Cub3D", 1);
	// if (!config->mlx)
	// 	printf("ERROR initializing MLX\n");
	// config->img = mlx_new_image(config->mlx, config->width, config->height);
	// if (!config->img
	// 	|| (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
	// 	printf("ERROR initializing MLX image\n");
	// init_config(config);
}
