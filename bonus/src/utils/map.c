/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:31:52 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/08 13:52:44 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	free_map(int **map, int size)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	get_tile_value(t_config *config, char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
	{
		config->orientation = c;
		return (5);
	}
	else if (c == 'D')
		return (4);
	else if (c == 'O')
		return (6);
	else if (c == 'T')
		return (2);
	else if (c == 'C')
		return (3);
	else if (c == '1')
		return (1);
	else
		return (0);
}

static int	get_rgba(int red, int green, int blue)
{
	return ((red << 24) | (green << 16) | (blue << 8) | 255);
}

int	**get_map(char **map_lines, t_config *config)
{
	int	i;
	int	j;
	int	**res;
	int	*row;

	i = 0;
	while (map_lines[i])
		i++;
	res = (int **) malloc(sizeof(int *) * (i + 1));
	if (!res)
		return (set_failure(config), NULL);
	i = 0;
	while (map_lines[i])
	{
		j = -1;
		row = (int *) malloc(sizeof(int) * (ft_strlen(map_lines[i]) - 1));
		if (!row)
			return (free_map(res, i), set_failure(config), NULL);
		while (map_lines[i][++j] && map_lines[i][j] != '\n')
			row[j] = get_tile_value(config, map_lines[i][j]);
		res[i] = row;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	init_map(t_config *config, t_tools *items)
{
	int			**map;
	int			width;
	int			height;

	config->c_color = get_rgba(ft_atoi(items->c_color[0]),
			ft_atoi(items->c_color[1]), ft_atoi(items->c_color[2]));
	config->f_color = get_rgba(ft_atoi(items->f_color[0]),
			ft_atoi(items->f_color[1]), ft_atoi(items->f_color[2]));
	config->path_n = items->path_NO;
	config->path_e = items->path_EA;
	config->path_w = items->path_WE;
	config->path_s = items->path_SO;
	map = get_map(items->maps, config);
	config->map = map;
	if (config->fail)
		return ;
	width = ft_strlen(items->maps[0]) - 1;
	height = 0;
	while (items->maps[height])
		height++;
	config->map_width = width;
	config->map_height = height;
}
