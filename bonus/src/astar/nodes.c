/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:08:37 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/08 17:24:48 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	swap_nodes(t_node **nodes, int i, int j)
{
	t_node	*tmp;

	tmp = nodes[j];
	nodes[j] = nodes[i];
	nodes[i] = tmp;
}

void	initialize_node(t_config *config, t_node *node, int x, int y)
{
	node->x = x;
	node->y = y;
	node->is_obstacle = 0;
	if (config->map[y][x] == 1 || config->map[y][x] == 4)
		node->is_obstacle = 1;
	node->visited = 0;
	node->local_goal = 2147483647.0f;
	node->global_goal = 2147483647.0f;
	node->parent = NULL;
	node->neighbors = (t_node **) malloc(sizeof(t_node *) * 4);
	if (!node->neighbors)
		return (set_failure(config));
	node->neighbors[NORTH] = NULL;
	node->neighbors[SOUTH] = NULL;
	node->neighbors[EAST] = NULL;
	node->neighbors[WEST] = NULL;
}

t_node	*allocate_nodes(t_config *config,
t_sprite *sprite, t_node **start, t_node **end)
{
	t_node	*nodes;
	int		i;
	int		j;

	nodes = (t_node *) malloc(sizeof(t_node)
			* config->map_width * config->map_height);
	if (!nodes)
		return (set_failure(config), NULL);
	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
			initialize_node(config, &nodes[i * config->map_width + j], j, i);
			if (config->fail)
				return (free_previous_nodes(nodes, i, j), NULL);
			if (is_sprite_node(sprite, i, j))
				*start = &nodes[i * config->map_width + j];
			if (is_player_node(config, i, j))
				*end = &nodes[i * config->map_width + j];
		}
	}
	return (nodes);
}

t_node	**get_nodes_to_check(t_config *config)
{
	t_node	**nodes_to_check;

	nodes_to_check = (t_node **) malloc(sizeof(t_node *)
			* config->map_width * config->map_height * 4);
	return (nodes_to_check);
}
