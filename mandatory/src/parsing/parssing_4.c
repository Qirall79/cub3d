/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:02:15 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/14 13:32:26 by wbelfatm         ###   ########.fr       */
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
				ft_putstr_fd("Error\nBad map\n", 2);
	}
	(1) && (cp = 0, i = -1);
	while (itms->map_2[++i])
	{
		if (!is_empty(itms->map_2[i]))
			(1) && (check(itms->map_2[i], itms), cp++);
		if (cp > 5)
			break ;
	}
	if (itms->cp_c != 1 || itms->cp_f != 1 || itms->cp_so != 1 || \
			itms->cp_no != 1 || itms->cp_ea != 1 || itms->cp_we != 1)
		ft_putstr_fd("Error\nBad texture\n", 2);
	if (update_map(itms, i + 1))
		ft_putstr_fd("Error\nBad map map\n", 2);
	return (1);
}

void	open_image(char *path, t_tools *itm, mlx_image_t *img)
{
	int	fd;

	(void)itm;
	(void)img;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Error\ninvalid texture file\n", 2);
	close(fd);
}

int	check_texture_1(char *s, t_tools *itms, void **p)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	(void)itms;
	(void)p;
	open_image(s, itms, (mlx_image_t *)p);
	return (0);
}
