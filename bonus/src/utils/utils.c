/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:29:38 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/07 13:04:53 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	vertical_facing(float angle)
{
	if (sin(angle * DEG_TO_RAD) > 0.000001f)
		return (1);
	else if (sin(angle * DEG_TO_RAD) < -0.000001f)
		return (2);
	return (0);
}

int	horizontal_facing(float angle)
{
	if (cos(angle * DEG_TO_RAD) > 0.000001f)
		return (1);
	else if (cos(angle * DEG_TO_RAD) < -0.000001f)
		return (2);
	return (0);
}

void	free_texture(t_config *config, int **texture, char op)
{
	int	height;
	int	i;

	height = config->height;
	if (op == 'u')
		height = UNIT;
	i = 0;
	while (i < height)
	{
		free(texture[i]);
		i++;
	}
	free(texture);
}

void free_items(t_tools *items)
{
	int i;

	i = 0;
	while (items->maps[i])
	{
		free(items->maps[i]);
		i++;
	}
	free(items->maps);
	items->maps = NULL;
	i = 0;
	while (i < 3)
	{
		free(items->f_color[i]);
		free(items->c_color[i]);	
		i++;	
	}
	free(items->f_color);
	free(items->c_color);
	i = 0;
	printf("\n\n");
	while (items->tmp_map[i])
	{
		free(items->tmp_map[i]);
		i++;
	}
	free(items->m_tmp);
	free(items->tmp_map);
}

void	free_config(t_config *config)
{
	int	i;

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
	free_items(config->items);
	free(config->rays);
}

void	set_failure(t_config *config)
{
	config->fail = true;
}
