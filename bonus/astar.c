/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:18:09 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/21 11:34:17 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float get_eucledian_distance(t_node *start, t_node *end)
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

	nodes = (t_node *) malloc(sizeof(t_node) * config->map_width * config->map_height);
	nodes_to_check = (t_node **) malloc(sizeof(t_node *) * config->map_width * config->map_height * 4);
	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
			nodes[i * config->map_width + j].x = j;
			nodes[i * config->map_width + j].y = i;
			nodes[i * config->map_width + j].is_obstacle = config->map[i][j] == 1 ? 1 : 0;
			nodes[i * config->map_width + j].visited = 0;
			nodes[i * config->map_width + j].local_goal = 2147483647;
			nodes[i * config->map_width + j].global_goal = 2147483647;
			nodes[i * config->map_width + j].parent = NULL;
			nodes[i * config->map_width + j].neighbors = (t_node **) malloc(sizeof(t_node *) * 4);
			nodes[i * config->map_width + j].neighbors[NORTH] = NULL;
			nodes[i * config->map_width + j].neighbors[SOUTH] = NULL;
			nodes[i * config->map_width + j].neighbors[EAST] = NULL;
			nodes[i * config->map_width + j].neighbors[WEST] = NULL;

			// set start and end
			if ((int)(config->sprite_pos.y / UNIT) == i
			&& (int)(config->sprite_pos.x / UNIT) == j)
				start = &nodes[i * config->map_width + j];
			if ((int)(config->yPos / UNIT) == i
			&& (int)(config->xPos / UNIT) == j)
				end = &nodes[i * config->map_width + j];
		}
	}

	// set neighbors
	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
			if (i > 0)
				nodes[i * config->map_width + j].neighbors[NORTH] = &nodes[(i - 1) * config->map_width + j];
			if (i < config->map_height - 1)
				nodes[i * config->map_width + j].neighbors[SOUTH] = &nodes[(i + 1) * config->map_width + j];
			if (j > 0)
				nodes[i * config->map_width + j].neighbors[WEST] = &nodes[i * config->map_width + j - 1];
			if (j < config->map_width - 1)
				nodes[i * config->map_width + j].neighbors[EAST] = &nodes[i * config->map_width + j + 1];
		}
	}

	// solving
	current = start;
	current->local_goal = 0.0;
	current->global_goal = get_eucledian_distance(start, end);
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
				new_local = current->local_goal + get_eucledian_distance(current, current->neighbors[i]);
				if (new_local < current->neighbors[i]->local_goal)
				{
					current->neighbors[i]->local_goal = new_local;
					current->neighbors[i]->parent = current;
					current->neighbors[i]->global_goal = new_local + get_eucledian_distance(current->neighbors[i], end);
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
	config->path_index = 0;
	config->path_to_player = path;
}


void solve_a_star_sprite(t_config *config, t_sprite *sprite)
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

	nodes = (t_node *) malloc(sizeof(t_node) * config->map_width * config->map_height);
	nodes_to_check = (t_node **) malloc(sizeof(t_node *) * config->map_width * config->map_height * 4);
	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
			nodes[i * config->map_width + j].x = j;
			nodes[i * config->map_width + j].y = i;
			nodes[i * config->map_width + j].is_obstacle = config->map[i][j] == 1 || config->map[i][j] == 4 ? 1 : 0;
			nodes[i * config->map_width + j].visited = 0;
			nodes[i * config->map_width + j].local_goal = 2147483647;
			nodes[i * config->map_width + j].global_goal = 2147483647;
			nodes[i * config->map_width + j].parent = NULL;
			nodes[i * config->map_width + j].neighbors = (t_node **) malloc(sizeof(t_node *) * 4);
			nodes[i * config->map_width + j].neighbors[NORTH] = NULL;
			nodes[i * config->map_width + j].neighbors[SOUTH] = NULL;
			nodes[i * config->map_width + j].neighbors[EAST] = NULL;
			nodes[i * config->map_width + j].neighbors[WEST] = NULL;

			// set start and end
			if ((int)(sprite->y / UNIT) == i
			&& (int)(sprite->x / UNIT) == j)
				start = &nodes[i * config->map_width + j];
			if ((int)(config->yPos / UNIT) == i
			&& (int)(config->xPos / UNIT) == j)
				end = &nodes[i * config->map_width + j];
		}
	}

	// set neighbors
	i = -1;
	while (++i < config->map_height)
	{
		j = -1;
		while (++j < config->map_width)
		{
			if (i > 0)
				nodes[i * config->map_width + j].neighbors[NORTH] = &nodes[(i - 1) * config->map_width + j];
			if (i < config->map_height - 1)
				nodes[i * config->map_width + j].neighbors[SOUTH] = &nodes[(i + 1) * config->map_width + j];
			if (j > 0)
				nodes[i * config->map_width + j].neighbors[WEST] = &nodes[i * config->map_width + j - 1];
			if (j < config->map_width - 1)
				nodes[i * config->map_width + j].neighbors[EAST] = &nodes[i * config->map_width + j + 1];
		}
	}

	// solving
	current = start;
	current->local_goal = 0.0;
	current->global_goal = get_eucledian_distance(start, end);
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
				new_local = current->local_goal + get_eucledian_distance(current, current->neighbors[i]);
				if (new_local < current->neighbors[i]->local_goal)
				{
					current->neighbors[i]->local_goal = new_local;
					current->neighbors[i]->parent = current;
					current->neighbors[i]->global_goal = new_local + get_eucledian_distance(current->neighbors[i], end);
				}
			}
			i++;
		}
	}
	free(nodes_to_check);
	sprite->path_steps = 0;
	start = current;
	while (start)
	{
		start = start->parent;
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
	sprite->path_to_player = path;
}