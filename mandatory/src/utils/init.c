/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:10:37 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/06 11:02:15 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_dimensions(t_config *config)
{
	config->width = WIDTH;
	config->height = HEIGHT;
}

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

float get_view_angle(t_config *config)
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
	config->fovAngle = 60.0;
	config->viewAngle = get_view_angle(config);
	config->dirY = sin(config->viewAngle * DEG_TO_RAD);
	config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	config->initial_player_x = config->xPos;
	config->initial_player_y = config->yPos;
	config->move_forward = 0;
	config->move_backward = 0;
	config->move_right = 0;
	config->move_left = 0;
	config->rotate_left = 0;
	config->rotate_right = 0;
}

void	init_game(t_config *config)
{
	/*---- parsing start ----*/
	set_dimensions(config);
	/*---- parsing end ----*/
	config->fail = 0;
	init_sprites_textures(config);
	if (config->fail)
		return ;
	set_pos(config);
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
