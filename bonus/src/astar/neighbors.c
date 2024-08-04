/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:11:08 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 16:01:52 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_node *	set_neighbors(t_config *config, t_node **nodes, t_sprite *sprite)
{
	int	i;
	int	j;
	t_node *current;

	current = NULL;
	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
			if ((*nodes)[i * config->map_width + j].x == (int)roundf((sprite->x) / UNIT)
			&& (*nodes)[i * config->map_width + j].y == (int)roundf((sprite->y) / UNIT))
				current = &((*nodes)[i * config->map_width + j]);
			if (i > 0)
				(*nodes)[i * config->map_width + j].neighbors[NORTH]
					= &(*nodes)[(i - 1) * config->map_width + j];
			if (i < config->map_height - 1)
				(*nodes)[i * config->map_width + j].neighbors[SOUTH]
					= &(*nodes)[(i + 1) * config->map_width + j];
			if (j > 0)
				(*nodes)[i * config->map_width + j].neighbors[WEST]
					= &(*nodes)[i * config->map_width + j - 1];
			if (j < config->map_width - 1)
				(*nodes)[i * config->map_width + j].neighbors[EAST]
					= &(*nodes)[i * config->map_width + j + 1];
		}
	}
	return current;
}

void	update_neighbors(t_node *current,
t_node *end, t_node **nodes_to_check, int *k)
{
	int		i;
	float	new_local;

	i = -1;
	current->visited = 1;
	while (++i < 4)
	{
		if (current->neighbors[i] && !current->neighbors[i]->visited
			&& !current->neighbors[i]->is_obstacle)
		{
			(nodes_to_check)[*k] = current->neighbors[i];
			(*k)++;
			new_local = current->local_goal
				+ get_eucledian_distance(current, current->neighbors[i]);
			if (new_local < current->neighbors[i]->local_goal)
			{
				current->neighbors[i]->local_goal = new_local;
				current->neighbors[i]->parent = current;
				current->neighbors[i]->global_goal = new_local
					+ get_eucledian_distance(current->neighbors[i], end);
			}
		}
	}
}
