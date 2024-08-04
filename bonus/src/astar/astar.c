/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:18:09 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 23:00:10 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	get_eucledian_distance(t_node *start, t_node *end)
{
	return (sqrtf((start->x - end->x) * (start->x - end->x)
			+ (start->y - end->y) * (start->y - end->y)));
}

int	list_empty(t_node **nodes_to_check, int k, t_node *current, t_node *end)
{
	int	i;

	if (current->x == end->x && current->y == end->y)
		return (1);
	i = 0;
	while (i < k)
	{
		if (!nodes_to_check[i]->visited)
			return (0);
		i++;
	}
	return (1);
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

void	init_current(t_node *current, t_node *end)
{
	current->local_goal = 0.0;
	current->global_goal = get_eucledian_distance(current, end);
}

void	solve_a_star(t_config *config, t_sprite *sprite)
{
	t_node	*nodes;
	t_node	*end;
	t_node	*current;
	t_node	**nodes_to_check;
	int		k;

	nodes = allocate_nodes(config, sprite, &current, &end);
	if (!nodes)
		return ;
	current = set_neighbors(config, &nodes, sprite);
	nodes_to_check = get_nodes_to_check(config);
	if (!nodes_to_check)
		return (free_nodes(config, nodes, NULL, 'f'));
	init_current(current, end);
	nodes_to_check[0] = current;
	k = 1;
	while (!list_empty(nodes_to_check, k, current, end))
	{
		sort_list(nodes_to_check, k, &current);
		if (!current)
			break ;
		update_neighbors(current, end, nodes_to_check, &k);
	}
	generate_path(config, sprite, current);
	free_nodes(config, nodes, nodes_to_check, 's');
}
