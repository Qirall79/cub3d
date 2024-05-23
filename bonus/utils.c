/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:29:38 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/23 12:11:33 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int vertical_facing(float angle)
{
	if (sin(angle * DEG_TO_RAD) > 0.000001f)
		return 1;
	else if (sin(angle * DEG_TO_RAD) < -0.000001f)
		return 2;
	return 0;
}

int horizontal_facing(float angle)
{
	if (cos(angle * DEG_TO_RAD) > 0.000001f)
		return 1;
	else if (cos(angle * DEG_TO_RAD) < -0.000001f)
		return 2;
	return 0;
}

void free_texture(t_config *config, int **texture, char op)
{
	int width;
	int i;

	width = config->width;
	if (op == 'u')
		width = UNIT;
	i = 0;
	while (i < width)
	{
		free(texture[i]);
		i++;
	}
	free(texture);
}

void free_config(t_config *config)
{
	int i;

	i = 0;
	while (i < config->sprite_count)
	{
		free(config->sprites[i].path_to_player);
		i++;
	}
	free(config->sprites);
	free_texture(config, config->texture_east, 'u');
	free_texture(config, config->texture_west, 'u');
	free_texture(config, config->texture_north, 'u');
	free_texture(config, config->texture_south, 'u');
	free_texture(config, config->enemy_texture, 'u');
	free_texture(config, config->collectible_texture, 'u');
	free_texture(config, config->door_texture, 'u');
	free_texture(config, config->win_texture, 'w');
	free_texture(config, config->loss_texture, 'w');
	free_texture(config, config->entry_texture, 'w');
	free(config->rays);
}

void set_failure(t_config *config)
{
	config->fail = true;
}