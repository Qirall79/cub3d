/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:38:22 by zmoumni           #+#    #+#             */
/*   Updated: 2024/08/07 13:16:22 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int is_empty(char *s)
{
	int i = 0;
	while (s && s[i] == ' ')
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return 1;
	return 0;
}

int	check_extention(char *s)
{
	int	i;

	i = ft_strlen(s);
	if (i <= 4)
		return (0);
	i--;
	if (s[i] == 'b' && s[i - 1] == 'u' && s[i - 2] == 'c' && s[i - 3] == '.')
		return (1);
	return (0);
}

void 	ft_init(t_tools *itms)
{
	itms->cp_C  = 0;
	itms->cp_F  = 0;
	itms->cp_SO = 0;
	itms->cp_NO = 0;
	itms->cp_EA = 0;
	itms->cp_WE = 0;
	itms->SNEW = 0;
	itms->cp__S = 0;
	itms->cp__N = 0;
	itms->cp__E = 0;
	itms->cp__W = 0;
	itms->path_C  = NULL;
	itms->path_F  = NULL;
	itms->path_SO = NULL;
	itms->path_NO = NULL;
	itms->path_EA = NULL;
	itms->path_WE = NULL;
	itms->maps = NULL;
	itms->player_x = 0;
	itms->player_y = 0;
}

int ft_read_map(char *name, t_tools *itms)
{
    int		fd;
	char	*str;
    itms->m_tmp = NULL;
    fd = open(name, O_RDONLY);
	if (check_extention(name) == 0 || fd < 0)
		ft_putstr_fd("Error\nInvalid file", 2);
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
		return (free(str), free(itms->m_tmp), ft_putstr_fd("Error\nBad map Map!", 2), 1);
    return (0);
}
char  **update(char **s, char *line)
{
	int i = 0;
	while (s && s[i])
		i++;
	char **rst = malloc((sizeof(char *) * (i + 2)));
	if (!rst)
		return NULL;
	i = 0;
	while (s && s[i])
	{
		rst[i] = ft_strdup(s[i]);
		i++;
	}
	rst[i++] = ft_strdup(line);
	rst[i] = NULL;
	return rst;
}

//***************************************

int check(char *s, t_tools *all)
{
	if (ft_strncmp(s, "NO ", 3))
		return (all->cp_NO++ ,all->path_NO = (s + 3), 1);
	else if (ft_strncmp(s, "SO ", 3))
		return (all->cp_SO++ ,all->path_SO = (s + 3), 1);
	else if (ft_strncmp(s, "WE ", 3))
		return (all->cp_WE++ ,all->path_WE = (s + 3), 1);
	else if (ft_strncmp(s, "EA ", 3))
		return (all->cp_EA++ ,all->path_EA = (s + 3), 1);
	else if (ft_strncmp(s, "C ", 2))
		return (all->cp_C++ ,all->path_C = (s + 2), 1);
	else if (ft_strncmp(s, "F ", 2))
		return (all->cp_F++ ,all->path_F = (s + 2), 1);
	else
		return (0);
}
void	get_yx(t_tools *itms)
{
	int len = 0;
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
void ft_hash(char *s, t_tools itms)
{
	int i = 0;
	while (i < itms.len_x - 1)
		s[i++] = '#';
	s[i++] = '\n';
	s[i] = '\0';
}
int update_map(t_tools *itms, int cp)
{
	int	j;
	int k; 

	j = 0;
	itms->map_2 += cp;
	get_yx(itms);
	itms->maps = (char **) malloc((itms->len_y + 1) * sizeof(char *));
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
	return 0;
}
/**********************************************/
int check_items(t_tools *itms)
{
    int i = 0;
    int cp = 0;
    while (itms->map_2 && itms->map_2[i])
	{
		cp = 0;
		while (itms->map_2[i][cp])
		{
			if (itms->map_2[i][cp++] == '\t')
				ft_putstr_fd("Error\nBad map", 2);
		}
        i++;
	}
    i = 0;
	cp = 0;
    while (itms->map_2[i])
    {
        if (!is_empty(itms->map_2[i]))
        {
            check(itms->map_2[i], itms);
            cp++;
        }
        if (cp > 5)
            break ;
        i++;
    }
    if (itms->cp_C != 1 || itms->cp_F != 1 || itms->cp_SO != 1 || itms->cp_NO != 1 || itms->cp_EA != 1 || itms->cp_WE != 1)
		ft_putstr_fd("Error\nBad texture ..", 2);
    if (update_map(itms, i + 1))
		ft_putstr_fd("Error\nBad map map", 2);
    return 1;
}

int is_valid(char *s, t_tools *all)
{
	int i = 0;
	
	while (s[i])
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == 'N'
		|| s[i] == 'S' || s[i] == 'E' || s[i] == 'W'
		|| s[i] == 'T' || s[i] == 'D' || s[i] == 'O'
		|| s[i] == 'C' || s[i] == ' ' || s[i] == '\n')
		{
			if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
			{
				all->SNEW++;
			}
			i++;
		}
		else
			return 1;
	}
	return 0;
}
int valid_edge(int i, int j, char **s)
{
	int cp = 0;
	if (s[i] && s[i][j + 1] && s[i][j + 1] != ' ')
		cp++;
	if (j != 0 && s[i] && s[i][j - 1] && s[i][j - 1] != ' ')
		cp++;
	if (s[i + 1] &&  s[i + 1][j] && s[i + 1][j] != ' ')
		cp++;
	if (i != 0 && s[i - 1] && s[i - 1][j] && s[i - 1][j] != ' ')
		cp++;
	if (cp == 4)
		return 0;
	return 1;
}
int is_valid_2(char c, t_tools *itms, int i, int j)
{

	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '0')
	{
		if (c == 'S')
		{
			itms->player_x = j * SIZE;
			itms->player_y = i * SIZE;
			itms->angle = PI / 2;
		}
		else if (c == 'N')
		{
			itms->player_x = j * SIZE;
			itms->player_y = i * SIZE;
			itms->angle = (3 * PI) / 2 ;
		}
		else if (c == 'E')
		{
			itms->player_x = j * SIZE;
			itms->player_y = i * SIZE;
			itms->angle =  0;
		}
		else if (c == 'W')
		{
			itms->player_x = j * SIZE;
			itms->player_y = i * SIZE;
			itms->angle = PI;
		}
		return 1;
	}
	return 0;
}
/******************************/
int is_valid_map(t_tools *itms)
{
	int i = 0;
	int j = 0;

	while(itms->maps[i][0] == '#')
		i++;
	while (itms->maps[i])
	{
		j = 0;
		if (is_valid(itms->map_2[i], itms))
			ft_putstr_fd("Error\nFound invalid caracter in map", 2);
		while (itms->maps[i][j])
		{
			if (is_valid_2(itms->maps[i][j], itms,i, j))
			{
				if (valid_edge(i, j, itms->maps))
					ft_putstr_fd("Error\nFound invalid caracter in map ??", 2);
			}
			j++;
		}
		i++;
	}
	if (itms->SNEW != 1)
		ft_putstr_fd("Error\nBad map direction in map", 2);
	return 0;
}
void open_image(char *path, t_tools *itm, mlx_image_t *img)
{
	mlx_texture_t *texture;
	// printf("|%s|\n",path);
	(void)img;
	(void)itm;
	// mlx_image_t *ptr = NULL;
	texture = mlx_load_png(path);
	if (!texture)
		ft_putstr_fd("Error\ninvalid texture file", 2);
	mlx_delete_texture(texture);
	// ptr = mlx_texture_to_image(itm->mlx, texture);
	// if (!ptr)
	// 	ft_putstr_fd("Error\ninvalid texture file", 2);
}
int check_texture_1(char *s, t_tools *itms, void **p)
{
	int i = 0;

	int end = 0;
	(void)i;
	(void)itms;
	(void)p;

	while (s && s[i] != '\n' && s[i] == ' ')
		i++;
	s+=i;
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
		return 0;
	}
	else
		return 1;
}
/************************/
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}
void function(char **s)
{
	int i = 0;
	int j = 0;
	int nb;
	while (s[i])
	{
		j = 0;
		while (s && s[i] && s[i][j] && is_digit(s[i][j]))
			j++;
		if (s[i][j] != '\0')
			ft_putstr_fd("Error\nBad texture", 2);
		
		nb = atoi(s[i]);
		if (nb < 0 || nb > 255)
			ft_putstr_fd("Error\nBad texture", 2);
		i++;
	}
	if (i != 3)
		ft_putstr_fd("Error\nBad texture", 2);

}

int	check_texture_2(char *s, t_tools *itms, char c)
{
	int	i;
	int	cp;
	int k ;

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
		ft_putstr_fd("Error\nBad texture", 2);
	s[k] = '\0';
	if (c == 'c')
	{
		itms->c_color = ft_split(s, ',');
		function(itms->c_color);
	}
	else
	{
		itms->f_color = ft_split(s, ',');
		function(itms->f_color);
	}
	return 0;
}

int	parssing(char *s, t_tools *itms)
{
	ft_read_map(s, itms);
	itms->map_2 = ft_split(itms->m_tmp, '#');
	itms->tmp_map = itms->map_2;
	ft_init(itms);
	check_items(itms);
	is_valid_map(itms);
	if (check_texture_1(itms->path_NO, itms, (void *)itms->N) || check_texture_1(itms->path_SO, itms, (void *)itms->S) \
		|| check_texture_1(itms->path_WE, itms, (void *)itms->W) || check_texture_1(itms->path_EA, itms, (void *)itms->E))
		ft_putstr_fd("Errpr\nBad texture !!!", 2);
	check_texture_2(itms->path_C, itms, 'c');
	check_texture_2(itms->path_F, itms, 'f');
    return (0);
}
