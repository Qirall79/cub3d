/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:46:56 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/13 17:49:36 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_init(t_tools *itms)
{
	itms->cp_c = 0;
	itms->cp_f = 0;
	itms->cp_so = 0;
	itms->cp_no = 0;
	itms->cp_ea = 0;
	itms->cp_we = 0;
	itms->snew = 0;
	itms->cp__s = 0;
	itms->cp__n = 0;
	itms->cp__e = 0;
	itms->cp__w = 0;
	itms->path_c = NULL;
	itms->path_f = NULL;
	itms->path_so = NULL;
	itms->path_no = NULL;
	itms->path_ea = NULL;
	itms->path_we = NULL;
	itms->maps = NULL;
	itms->player_x = 0;
	itms->player_y = 0;
}

int	is_valid(char *s, t_tools *all)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '#')
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == 'N' \
			|| s[i] == 'S' || s[i] == 'E' || s[i] == 'W' \
			|| s[i] == ' ' || s[i] == '\n'
			|| s[i] == 'D' || s[i] == 'O'
			|| s[i] == 'C' || s[i] == 'T')
		{
			if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
				all->snew++;
			i++;
		}
		else
			return (1);
	}
	return (0);
}

int	valid_edge(int i, int j, char **s)
{
	int	cp;

	cp = 0;
	if (s[i] && s[i][j + 1] && s[i][j + 1] != '#' && s[i][j + 1] != ' ')
		cp++;
	if (j != 0 && s[i] && s[i][j - 1] && s[i][j - 1] != '#' && s[i][j - 1] != ' ')
		cp++;
	if (s[i + 1] && s[i + 1][j] && s[i + 1][j] != '#' && s[i + 1][j] != ' ')
		cp++;
	if (i != 0 && s[i - 1] && s[i - 1][j] && s[i - 1][j] != '#' && s[i - 1][j] != ' ')
		cp++;
	if (cp == 4)
		return (0);
	return (1);
}

int	is_valid_2(char c, t_tools *itms, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '0')
	{
		if (c == 'S')
		{
			(1) && (itms->player_x = j * SIZE, itms->player_y = i * SIZE, \
				itms->angle = M_PI / 2);
		}
		else if (c == 'N')
		{
			(1) && (itms->player_x = j * SIZE, itms->player_y = i * SIZE, \
			itms->angle = (3 * M_PI) / 2);
		}
		else if (c == 'E')
		{
			(1) && (itms->player_x = j * SIZE, itms->player_y = i * SIZE, \
			itms->angle = 0);
		}
		else if (c == 'W')
		{
			(1) && (itms->player_x = j * SIZE, itms->player_y = i * SIZE, \
			itms->angle = M_PI);
		}
		return (1);
	}
	return (0);
}

int	is_valid_map(t_tools *itms)
{
	int	i;
	int	j;

	i = 0;
	while (itms->maps[i][0] == '#')
		i++;
	while (itms->maps[i])
	{
		j = 0;
		if (is_valid(itms->maps[i], itms))
			ft_putstr_fd("Error\nBad map /*/\n", 2);
		while (itms->maps[i][j])
		{
			if (is_valid_2(itms->maps[i][j], itms, i, j))
			{
				if (valid_edge(i, j, itms->maps))
					ft_putstr_fd("Error\nFound invalid caracter in map !\n", 2);
			}
			j++;
		}
		i++;
	}
	if (itms->snew != 1)
		ft_putstr_fd("Error\nBad direction in map\n", 2);
	return (0);
}
