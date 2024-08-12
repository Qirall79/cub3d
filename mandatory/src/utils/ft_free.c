/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:56:30 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/12 18:37:46 by wbelfatm         ###   ########.fr       */
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

void	free_items(t_tools *items)
{
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
}

void	free_config(t_config *config)
{
	// free_texture(config, config->texture_east, 'u');
	// free_texture(config, config->texture_west, 'u');
	// free_texture(config, config->texture_north, 'u');
	// free_texture(config, config->texture_south, 'u');
	free_items(config->items);
}
