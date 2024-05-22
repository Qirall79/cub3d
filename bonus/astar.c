/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:18:09 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/22 13:36:04 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_eucledian_distance(t_node *start, t_node *end)
{
	return (sqrtf((start->x - end->x) * (start->x - end->x)
			+ (start->y - end->y) * (start->y - end->y)));
}

int	list_empty(t_node **nodes_to_check, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (!nodes_to_check[i]->visited)
			return (0);
		i++;
	}
	return (1);
}

void	swap_nodes(t_node **nodes, int i, int j)
{
	t_node	*tmp;

	tmp = nodes[j];
	nodes[j] = nodes[i];
	nodes[i] = tmp;
}

void	sort_list(t_node **nodes_to_check, int end, t_node **current)
{
	int	i;
	int	j;

	i = 0;
	while (i < end && nodes_to_check[i]->visited)
		i++;
	while (i < end)
	{
		j = i + 1;
		while (j < end)
		{
			if (nodes_to_check[j]->global_goal < nodes_to_check[i]->local_goal)
				swap_nodes(nodes_to_check, i, j);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < end && nodes_to_check[i]->visited)
		i++;
	if (i < end)
		*current = nodes_to_check[i];
	else
		*current = NULL;
}

void	initialize_node(t_config *config, t_node *node, int x, int y)
{
	node->x = x;
	node->y = y;
	node->is_obstacle = 0;
	if (config->map[y][x] == 1 || config->map[y][x] == 4)
		node->is_obstacle = 1;
	node->visited = 0;
	node->local_goal = 2147483647;
	node->global_goal = 2147483647;
	node->parent = NULL;
	node->neighbors = (t_node **) malloc(sizeof(t_node *) * 4);
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
		return (NULL);
	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
			initialize_node(config, &nodes[i * config->map_width + j], j, i);
			if ((int)(sprite->y / UNIT) == i
			&& (int)(sprite->x / UNIT) == j)
				*start = &nodes[i * config->map_width + j];
			if ((int)(config->yPos / UNIT) == i
			&& (int)(config->xPos / UNIT) == j)
				*end = &nodes[i * config->map_width + j];
		}
	}
	return (nodes);
}

void	set_neighbors(t_config *config, t_node **nodes)
{
	int	i;
	int	j;

	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
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
}

void	update_neighbors(t_node *current,
t_node *end, t_node **nodes_to_check, int *k)
{
	int		i;
	float	new_local;

	i = -1;
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

void	generate_path(t_sprite *sprite, t_node *current)
{
	t_vector	*path;
	t_node		*tmp;
	int			i;

	sprite->path_steps = 0;
	tmp = current;
	while (tmp)
	{
		tmp = tmp->parent;
		sprite->path_steps++;
	}
	path = (t_vector *) malloc(sizeof(t_vector) * sprite->path_steps);
	i = 0;
	while (current)
	{
		path[sprite->path_steps - i - 1].x = current->x;
		path[sprite->path_steps - i - 1].y = current->y;
		current = current->parent;
		i++;
	}
	sprite->path_index = 0;
	free(sprite->path_to_player);
	sprite->path_to_player = path;
}

void	solve_a_star(t_config *config, t_sprite *sprite)
{
	t_node	*nodes;
	t_node	*end;
	t_node	*current;
	t_node	**nodes_to_check;
	int		k;

	nodes = allocate_nodes(config, sprite, &current, &end);
	set_neighbors(config, &nodes);
	nodes_to_check = (t_node **) malloc(sizeof(t_node *)
			* config->map_width * config->map_height * 4);
	current->local_goal = 0.0;
	current->global_goal = get_eucledian_distance(current, end);
	nodes_to_check[0] = current;
	k = 1;
	while (!list_empty(nodes_to_check, k)
		&& !(current->x == end->x && current->y == end->y))
	{
		sort_list(nodes_to_check, k, &current);
		if (!current)
			return ;
		current->visited = 1;
		update_neighbors(current, end, nodes_to_check, &k);
	}
	free(nodes_to_check);
	generate_path(sprite, current);
}
