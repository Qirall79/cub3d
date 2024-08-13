/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:25:03 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/13 08:49:51 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include <libc.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define SIZE 32
# define SIZE_P 5
# define BUFFER_SIZE 20

typedef struct tools
{
	char		**tmp_map;
	char		**map;
	char		**map_origin;
	char		*m_tmp;
	double		ray_angle;
	char		**map_2;
	char		**maps;
	char		*tmp;
	int			cp_no;
	int			cp_so;
	int			cp_we;
	int			cp_ea;
	int			cp_f;
	int			cp_c;
	char		*path_we;
	char		*path_ea;
	char		*path_no;
	char		*path_so;
	char		*path_c;
	char		*path_f;
	int			snew;
	int			cp__s;
	int			cp__n;
	int			cp__e;
	int			cp__w;
	int			len_y;
	int			len_x;
	double		player_x;
	double		player_y;
	double		end_y;
	double		end_x;
	double		angle;
	int			line_len;
	xpm_t		*w;
	xpm_t		*e;
	xpm_t		*n;
	xpm_t		*s;
	char		**c_color;
	char		**f_color;
	mlx_t		*mlx;
	mlx_image_t	*mini;
	double		face_up;
	double		face_down;
	double		face_left;
	double		face_right;
}	t_tools;

/*p-5*/
int		is_valid_map(t_tools *itms);
void	open_image(char *path, t_tools *itm, mlx_image_t *img);
int		check_texture_1(char *s, t_tools *itms, void **p);

/*p-4*/
int		check_items(t_tools *itms);
int		is_valid(char *s, t_tools *all);
int		valid_edge(int i, int j, char **s);
int		is_valid_2(char c, t_tools *itms, int i, int j);

/*p-3*/
int		check(char *s, t_tools *all);
void	get_yx(t_tools *itms);
void	ft_hash(char *s, t_tools itms);
int		update_map(t_tools *itms, int cp);

/*p-2*/
int		is_empty(char *s);
int		check_extention(char *s);
void	ft_init(t_tools *itms);
int		ft_read_map(char *name, t_tools *itms);
char	**update(char **s, char *line);
int		is_digit(char c);
void	function(char **s);
int		check_texture_2(char *s, t_tools *itms, char c);
int		parssing(char *s, t_tools *itms);
char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
int		ft_strncmp(char *s1, char *s2, int c);
char	**free_2d(char **tbl);
int		ft_strncmp(char *s1, char *s2, int c);
char	*ft_strtrim(char	*s1, char	*set);
int		is_empty_line(t_tools *itms);
void	skip_line(t_tools *itms);

#endif