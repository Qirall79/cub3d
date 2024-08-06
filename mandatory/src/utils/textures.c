/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:03:15 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/04 23:01:03 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

uint32_t	abgr_to_rgba(uint32_t abgr_color)
{
	uint8_t	alpha;
	uint8_t	blue;
	uint8_t	green;
	uint8_t	red;

	alpha = (abgr_color >> 24) & 0xFF;
	blue = (abgr_color >> 16) & 0xFF;
	green = (abgr_color >> 8) & 0xFF;
	red = abgr_color & 0xFF;
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

void	load_texture(t_config *config, char *path)
{
	mlx_texture_t	*tex;

	if (config->fail)
		return ;
	tex = mlx_load_png(path);
	if (!tex)
		return (set_failure(config));
	config->tex = tex;
}

int	**generate_texture(char *path, t_config *config, t_dimensions d)
{
	int				**arr;
	int				*pixels;
	int				x;
	int				y;

	load_texture(config, path);
	arr = allocate_texture(config, d);
	if (!arr || config->fail)
		return (set_failure(config), NULL);
	pixels = (int *) config->tex->pixels;
	y = 0;
	while (y < d.height)
	{
		x = 0;
		while (x < d.width)
		{
			arr[y][x] = abgr_to_rgba(
					pixels[get_color_index(config->tex, x, y, d)]);
			x++;
		}
		y++;
	}
	mlx_delete_texture(config->tex);
	return (arr);
}

int	**allocate_texture(t_config *config, t_dimensions d)
{
	int	**arr;
	int	y;
	int	i;

	if (config->fail)
		return (NULL);
	arr = (int **)malloc(d.height * sizeof(int *));
	if (!arr)
		return (set_failure(config), NULL);
	y = 0;
	while (y < d.height)
	{
		arr[y] = (int *)malloc(d.width * sizeof(int));
		if (!arr[y])
		{
			i = -1;
			while (++i < y)
				free(arr[i]);
			return (set_failure(config), NULL);
		}
		y++;
	}
	return (arr);
}

int	get_color_index(mlx_texture_t *tex, int x, int y, t_dimensions d)
{
	int	i;
	int	j;

	i = (int)floorf(y * (tex->height / (float)d.height));
	j = (int)floorf(x * (tex->width / (float)d.width));
	return (i * tex->width + j);
}
