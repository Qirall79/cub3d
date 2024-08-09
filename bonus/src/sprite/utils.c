/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:29:55 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:09:34 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_sprites_distance(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->sprite_count)
	{
		config->sprites[i].distance = get_distance(config->sprites[i].x,
				config->sprites[i].y, config->x_pos, config->y_pos);
		i++;
	}
}

void	move_all(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->sprite_count)
	{
		if (config->sprites[i].type == ENEMY)
			move_sprite(config, &config->sprites[i]);
		i++;
	}
}

void	sort_sprites(t_config *config)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < config->sprite_count)
	{
		j = i + 1;
		while (j < config->sprite_count)
		{
			if (config->sprites[i].distance < config->sprites[j].distance)
			{
				tmp = config->sprites[i];
				config->sprites[i] = config->sprites[j];
				config->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	is_drawable(t_config *config, t_vector texture_pos, t_sprite *sprite, int x)
{
	if (in_range(texture_pos.x, 0, UNIT)
		&& in_range(texture_pos.y, 0, UNIT)
		&& (char)sprite->texture[(int)texture_pos.y][(int)texture_pos.x]
		&& (int)roundf(sprite->distance) <= config->rays[x])
		return (1);
	return (0);
}
