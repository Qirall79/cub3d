/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumni <zmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:38:22 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/12 13:13:20 by zmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	check_color(char **s)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		while (s && s[i] && s[i][j] && is_digit(s[i][j]))
			j++;
		if (s[i][j] != '\0')
			ft_putstr_fd("Error\nBad texture\n", 2);
		nb = atoi(s[i]);
		if (nb < 0 || nb > 255)
			ft_putstr_fd("Error\nBad texture\n", 2);
		i++;
	}
	if (i != 3)
		ft_putstr_fd("Error\nBad texture\n", 2);
}

void	helper(char *s, char c, t_tools *itms)
{
	if (c == 'c')
	{
		itms->c_color = ft_split(s, ',');
		check_color(itms->c_color);
	}
	else
	{
		itms->f_color = ft_split(s, ',');
		check_color(itms->f_color);
	}
}

int	check_texture_2(char *s, t_tools *itms, char c)
{
	int	i;
	int	cp;
	int	k;

	i = 0;
	cp = 0;
	while (s && s[i] && s[i] == ' ')
		i++;
	s += i;
	i = 0;
	while (s && s[i] && s[i] != '\n' && s[i] != ' ')
	{
		if (s[i] == ',')
			cp++;
		i++;
	}
	if (s[i] == '\n')
		k = i++;
	while (s && s[i] && s[i] == ' ')
		i++;
	if (s[i] != '\0' || cp != 2)
		ft_putstr_fd("Error\nBad texture\n", 2);
	s[k] = '\0';
	helper(s, c, itms);
	return (0);
}

int	parssing(char *s, t_tools *itms)
{
	ft_read_map(s, itms);
	itms->map_2 = ft_split(itms->m_tmp, '#');
	itms->tmp_map = itms->map_2;
	ft_init(itms);
	check_items(itms);
	is_empty_line(itms);
	is_valid_map(itms);
	if (check_texture_1(itms->path_no, itms, (void *)itms->n) \
		|| check_texture_1(itms->path_so, itms, (void *)itms->s) \
			|| check_texture_1(itms->path_we, itms, (void *)itms->w) \
				|| check_texture_1(itms->path_ea, itms, (void *)itms->e))
		ft_putstr_fd("Error\nBad texture", 2);
	check_texture_2(itms->path_c, itms, 'c');
	check_texture_2(itms->path_f, itms, 'f');
	return (0);
}
