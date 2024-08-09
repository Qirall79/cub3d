/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumni <zmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:02:15 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/08 18:45:36 by zmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_items(t_tools *itms)
{
	int	i;
	int	cp;

	i = -1;
	while (itms->map_2 && itms->map_2[++i])
	{
		cp = 0;
		while (itms->map_2[i][cp])
			if (itms->map_2[i][cp++] == '\t')
				ft_putstr_fd("Error\nBad map", 2);
	}
	(1) && (cp = 0, i = -1);
	while (itms->map_2[++i])
	{
		if (!is_empty(itms->map_2[i]))
			(1) && (check(itms->map_2[i], itms), cp++);
		if (cp > 5)
			break ;
	}
	if (itms->cp_C != 1 || itms->cp_F != 1 || itms->cp_SO != 1 || \
			itms->cp_NO != 1 || itms->cp_EA != 1 || itms->cp_WE != 1)
		ft_putstr_fd("Error\nBad texture", 2);
	if (update_map(itms, i + 1))
		ft_putstr_fd("Error\nBad map map", 2);
	return (1);
}

void	open_image(char *path, t_tools *itm, mlx_image_t *img)
{
	mlx_texture_t	*texture;

	(void)itm;
	(void)img;
	texture = mlx_load_png(path);
	if (!texture)
		ft_putstr_fd("Error\ninvalid texture file", 2);
	mlx_delete_texture(texture);
}

int	check_texture_1(char *s, t_tools *itms, void **p)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while (s && s[i] != '\n' && s[i] == ' ')
		i++;
	s += i;
	while (s && s[i] != '\n' && s[i] != ' ')
		i++;
	end = i;
	while (s && s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\n')
		i++;
	if (s[i] == '\0')
	{
		s[end] = '\0';
		open_image(s, itms, (mlx_image_t *)p);
		return (0);
	}
	else
		return (1);
}
