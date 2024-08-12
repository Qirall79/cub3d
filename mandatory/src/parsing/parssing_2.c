/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumni <zmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:46:54 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/12 13:43:08 by zmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_read_map(char *name, t_tools *itms)
{
	int		fd;
	char	*str;

	itms->m_tmp = NULL;
	fd = open(name, O_RDONLY);
	if (check_extention(name) == 0 || fd < 0)
		ft_putstr_fd("Error\nInvalid file\n", 2);
	str = get_next_line(fd);
	while (str)
	{
		itms->m_tmp = ft_strjoin(itms->m_tmp, str);
		itms->m_tmp = ft_strjoin(itms->m_tmp, "#");
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	if (!itms->m_tmp)
		return (free(str), free(itms->m_tmp), \
			ft_putstr_fd("Error\nBad map Map!\n", 2), 1);
	return (0);
}

int	check(char *s, t_tools *all)
{
	if (ft_strncmp(s, "NO ", 3))
		return (all->cp_no++, s += 3, all->path_no = ft_strtrim(s, " \t\n"), 1);
	else if (ft_strncmp(s, "SO ", 3))
		return (all->cp_so++, s += 3, all->path_so = ft_strtrim(s, " \t\n"), 1);
	else if (ft_strncmp(s, "WE ", 3))
		return (all->cp_we++, s += 3, all->path_we = ft_strtrim(s, " \t\n"), 1);
	else if (ft_strncmp(s, "EA ", 3))
		return (all->cp_ea++, s += 3, all->path_ea = ft_strtrim(s, " \t\n"), 1);
	else if (ft_strncmp(s, "C ", 2))
		return (all->cp_c++, s += 2, all->path_c = ft_strtrim(s, " \t\n"), 1);
	else if (ft_strncmp(s, "F ", 2))
		return (all->cp_f++, s += 2, all->path_f = ft_strtrim(s, " \t\n"), 1);
	else
		return (0);
}

void	get_yx(t_tools *itms)
{
	int	len;

	len = 0;
	itms->len_x = 0;
	itms->len_y = 0;
	while (itms->map_2[itms->len_y])
	{
		len = ft_strlen(itms->map_2[itms->len_y]);
		if (len > itms->len_x)
			itms->len_x = len;
		itms->len_y++;
	}
}

void	ft_hash(char *s, t_tools itms)
{
	int	i;

	i = 0;
	while (i < itms.len_x - 1)
		s[i++] = '#';
	s[i++] = '\n';
	s[i] = '\0';
}

int	update_map(t_tools *itms, int cp)
{
	int	j;
	int	k;

	j = 0;
	itms->map_2 += cp;
	get_yx(itms);
	itms->maps = (char **)malloc((itms->len_y + 1) * sizeof(char *));
	if (!itms->maps)
		return (1);
	while (j < itms->len_y)
	{
		itms->maps[j] = (char *)malloc((itms->len_x + 1) * sizeof(char));
		if (!itms->maps[j])
			return (free_2d(itms->maps), 1);
		ft_hash(itms->maps[j], *itms);
		k = 0;
		while (itms->map_2[j][k] && itms->map_2[j][k] != '\n')
		{
			itms->maps[j][k] = itms->map_2[j][k];
			k++;
		}
		j++;
	}
	itms->maps[itms->len_y] = (NULL);
	return (skip_line(itms), 0);
}
