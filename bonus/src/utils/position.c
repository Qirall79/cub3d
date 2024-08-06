/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:07:39 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/06 10:22:08 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
		.texture = config->enemy_texture,
		.path_to_player = NULL
	};
	if (config->sprites[index].type == COLLECTIBLE)
	{
		config->sprites[index].texture = config->collectible_texture;
		config->collectibles_left++;
		config->no_collectibles = 0;
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

void	assign_paths(t_config *config)
{
	int	i;

	if (config->fail)
		return ;
	i = 0;
	while (i < config->sprite_count)
	{
		if (config->sprites[i].type == ENEMY)
			solve_a_star(config, &config->sprites[i]);
		if (config->fail)
			break ;
		i++;
	}
}
