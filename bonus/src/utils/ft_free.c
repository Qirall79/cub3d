/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:56:30 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/13 09:01:22 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	free_str_arr(char **arr, char op)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (op)
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

void	free_items(t_config *config)
{
	t_tools	*items;
	int		i;

	items = config->items;
	free_str_arr(items->maps, 0);
	free(items->map_origin);
	items->maps = NULL;
	free_str_arr(items->f_color, 1);
	free_str_arr(items->c_color, 1);
	free_str_arr(items->tmp_map, 1);
	free(items->m_tmp);
	free(items->path_c);
	free(items->path_f);
	free(items->path_no);
	free(items->path_so);
	free(items->path_we);
	free(items->path_ea);
	i = 0;
	while (config->map[i])
	{
		free(config->map[i]);
		i++;
	}
	free(config->map);
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
	free_items(config);
	free(config->rays);
}

void	free_previous_nodes(t_node *nodes, int i, int j)
{
	int	y;
	int	x;

	y = 0;
	while (y <= i)
	{
		x = 0;
		while (x <= j)
		{
			free(nodes[y * MAP_WIDTH + x].neighbors);
			x++;
		}
		y++;
	}
	free(nodes);
}
