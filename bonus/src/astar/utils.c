/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:13:47 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:06:08 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_sprite_node(t_sprite *sprite, int i, int j)
{
	if ((int)(sprite->y / UNIT) == i
		&& (int)(sprite->x / UNIT) == j)
		return (1);
	return (0);
}

int	is_player_node(t_config *config, int i, int j)
{
	if ((int)(config->y_pos / UNIT) == i
		&& (int)(config->x_pos / UNIT) == j)
		return (1);
	return (0);
}

void	free_nodes(t_config *config, t_node *nodes,
t_node **nodes_to_check, char op)
{
	int	i;
	int	j;

	i = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			free(nodes[i * config->map_width + j].neighbors);
			j++;
		}
		i++;
	}
	free(nodes);
	free(nodes_to_check);
	if (op == 'f')
		set_failure(config);
}

void	free_path(t_sprite *sprite)
{
	free(sprite->path_to_player);
	sprite->path_to_player = NULL;
}

void	generate_path(t_config *config, t_sprite *sprite, t_node *current)
{
	t_vector	*path;
	t_node		*tmp;
	int			i;

	sprite->path_steps = 0;
	tmp = current;
	free_path(sprite);
	while (tmp)
	{
		tmp = tmp->parent;
		sprite->path_steps++;
	}
	path = (t_vector *) malloc(sizeof(t_vector) * sprite->path_steps);
	if (!path)
		return (set_failure(config));
	i = 0;
	while (current)
	{
		path[sprite->path_steps - i - 1].x = current->x;
		path[sprite->path_steps - i - 1].y = current->y;
		current = current->parent;
		i++;
	}
	sprite->path_index = 0;
	sprite->path_to_player = path;
}
