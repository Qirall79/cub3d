/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:56:30 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/07 14:01:04 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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

void	free_items(t_tools *items)
{
	free_str_arr(items->maps);
	items->maps = NULL;
	free_str_arr(items->f_color);
	free_str_arr(items->c_color);
	free_str_arr(items->tmp_map);
	free(items->m_tmp);
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
