/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:48:34 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/06 10:58:41 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void	end_game(t_config *config)
{
	mlx_terminate(config->mlx);
	free_config(config);
	exit(EXIT_SUCCESS);
}

void	handle_click(mlx_key_data_t keydata, t_config *config)
{
	set_movement_params(keydata, config);
	if (keydata.key == MLX_KEY_ESCAPE)
		end_game(config);
}

void	handle_mouse(double xpos, double ypos, t_config *config)
{
	double	increment;

	(void) ypos;
	increment = (xpos - config->width / 2.0) / 8;
	config->viewAngle = normalize_angle(config->viewAngle + increment);
	config->dirY = sin(config->viewAngle * DEG_TO_RAD);
	config->dirX = cos(config->viewAngle * DEG_TO_RAD);
	mlx_set_mouse_pos(config->mlx, config->width / 2.0, config->height / 2.0);
}
