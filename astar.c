/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:18:09 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/18 22:04:54 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float get_distance(t_node *start, t_node *end)
{
	return (sqrtf((start->x - end->x) * (start->x - end->x) + (start->y - end->y) * (start->y - end->y)));
}

int list_empty(t_node **nodes_to_check, int end)
{
	int i;

	i = 0;
	while (i < end)
	{
		if (!nodes_to_check[i]->visited)
			return (0);
		i++;
	}
	return (1);
}

void sort_list(t_node **nodes_to_check, int end)
{
	t_node *tmp;
	int i;
	int j;

	i = 0;
	while (i < end && nodes_to_check[i]->visited)
		i++;
	while (i < end)
	{
		j = i + 1;
		while (j < end)
		{
			if (nodes_to_check[j]->global_goal < nodes_to_check[i]->local_goal)
			{
				tmp = nodes_to_check[j];
				nodes_to_check[j] = nodes_to_check[i];
				nodes_to_check[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

void solve_a_star(t_config *config)
{
	t_node *nodes;
	t_node *start;
	t_node *end;
	t_node *current;
	t_node **nodes_to_check;
	t_vector *path;
	int k;
	int i;
	int j;
	float new_local;

	nodes = (t_node *) malloc(sizeof(t_node) * MAP_WIDTH * MAP_HEIGHT);
	nodes_to_check = (t_node **) malloc(sizeof(t_node *) * MAP_WIDTH * MAP_HEIGHT * 4);
	i = -1;
	while (++i < MAP_HEIGHT)
	{
		j = -1;
		while (++j < MAP_WIDTH)
		{
			nodes[i * MAP_WIDTH + j].x = j;
			nodes[i * MAP_WIDTH + j].y = i;
			nodes[i * MAP_WIDTH + j].is_obstacle = config->map[i][j] == 1 ? 1 : 0;
			nodes[i * MAP_WIDTH + j].visited = 0;
			nodes[i * MAP_WIDTH + j].local_goal = 2147483647;
			nodes[i * MAP_WIDTH + j].global_goal = 2147483647;
			nodes[i * MAP_WIDTH + j].parent = NULL;
			nodes[i * MAP_WIDTH + j].neighbors = (t_node **) malloc(sizeof(t_node *) * 4);
			nodes[i * MAP_WIDTH + j].neighbors[NORTH] = NULL;
			nodes[i * MAP_WIDTH + j].neighbors[SOUTH] = NULL;
			nodes[i * MAP_WIDTH + j].neighbors[EAST] = NULL;
			nodes[i * MAP_WIDTH + j].neighbors[WEST] = NULL;

			// set start and end
			if ((int)(config->sprite_pos.y / UNIT) == i
			&& (int)(config->sprite_pos.x / UNIT) == j)
				start = &nodes[i * MAP_WIDTH + j];
			if ((int)(config->yPos / UNIT) == i
			&& (int)(config->xPos / UNIT) == j)
				end = &nodes[i * MAP_WIDTH + j];
		}
	}

	// set neighbors
	i = -1;
	while (++i < MAP_HEIGHT)
	{
		j = -1;
		while (++j < MAP_WIDTH)
		{
			if (i > 0)
				nodes[i * MAP_WIDTH + j].neighbors[NORTH] = &nodes[(i - 1) * MAP_WIDTH + j];
			if (i < MAP_HEIGHT - 1)
				nodes[i * MAP_WIDTH + j].neighbors[SOUTH] = &nodes[(i + 1) * MAP_WIDTH + j];
			if (j > 0)
				nodes[i * MAP_WIDTH + j].neighbors[WEST] = &nodes[i * MAP_WIDTH + j - 1];
			if (j < MAP_WIDTH - 1)
				nodes[i * MAP_WIDTH + j].neighbors[EAST] = &nodes[i * MAP_WIDTH + j + 1];
		}
	}

	// solving
	current = start;
	current->local_goal = 0.0;
	current->global_goal = get_distance(start, end);
	k = 0;
	nodes_to_check[k] = current;
	k++;
	while (!list_empty(nodes_to_check, k) && !(current->x == end->x && current->y == end->y))
	{
		i = 0;
		sort_list(nodes_to_check, k);
		while (i < k && nodes_to_check[i]->visited)
			i++;
		if (i == k)
			break ;
		current = nodes_to_check[i];
		current->visited = 1;
		i = 0;
		while (i < 4)
		{
			// each neighbor
			if (current->neighbors[i] && !current->neighbors[i]->visited
			&& !current->neighbors[i]->is_obstacle)
			{
				nodes_to_check[k] = current->neighbors[i];
				k++;
				new_local = current->local_goal + get_distance(current, current->neighbors[i]);
				if (new_local < current->neighbors[i]->local_goal)
				{
					current->neighbors[i]->local_goal = new_local;
					current->neighbors[i]->parent = current;
					current->neighbors[i]->global_goal = new_local + get_distance(current->neighbors[i], end);
				}
			}
			i++;
		}
	}
	free(nodes_to_check);
	config->path_steps = 0;
	start = current;
	while (start)
	{
		start = start->parent;
		config->path_steps++;
	}
	path = (t_vector *) malloc(sizeof(t_vector) * config->path_steps);
	i = 0;
	while (current)
	{
		path[config->path_steps - i - 1].x = current->x;
		path[config->path_steps - i - 1].y = current->y;
		current = current->parent;
		i++;
	}
	config->path_to_player = path;
}