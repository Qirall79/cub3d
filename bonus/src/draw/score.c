/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:17:00 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/09 11:17:32 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	draw_pixel(t_config *config, t_vector p, int i, int j)
{
	if (in_range(p.x, 0, config->width - 1)
		&& in_range(p.y, 0, config->height - 1)
		&& (char)config->collectible_texture[i][j])
		mlx_put_pixel(config->img, p.x, p.y, config->collectible_texture[i][j]);
}

void	draw_score(t_config *config)
{
	int			i;
	int			j;
	t_vector	p;
	int			n;

	n = config->collectibles_left;
	while (n > 0)
	{
		i = 0;
		p.y = HEIGHT - (40 * n);
		while (i < UNIT)
		{
			j = 0;
			p.x = 8;
			while (j < UNIT)
			{
				draw_pixel(config, p, i, j);
				j += UNIT / 32;
				p.x++;
			}
			p.y++;
			i += UNIT / 32;
		}
		n--;
	}
}
