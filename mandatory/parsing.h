# ifndef CUB_3D
# define CUB_3D

# include <libc.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

#include <math.h>
// # include "MLX42/include/MLX42/MLX42.h"

// # include <mlx.h>


# define SIZE 32
# define SIZE_P 5
# define BUFFER_SIZE 20
# define PI 3.141592653589793238462643383279502884197
# define r_speed (5 * (PI / 180))
# define p_speed 5


// #define C1  0x02E4374

typedef struct tools
{
    char **tmp_map;
    char **map;
    char *m_tmp;
    double ray_angle;
    char **map_2;
    char **maps;
    char *tmp;
    int cp_NO;
    int cp_SO;
    int cp_WE;
    int cp_EA;
    int cp_F;
    int cp_C;
    char *path_WE;
    char *path_EA;
    char *path_NO;
    char *path_SO;
    char *path_C;
    char *path_F;
    int SNEW;
    int cp__S;
    int cp__N;
    int cp__E;
    int cp__W;
    int len_y; // i
    int len_x; // j

    double      player_x;
    double      player_y;
    double      end_y;
    double      end_x;
    double     angle;
    int         line_len;
    xpm_t *W;
    xpm_t *E;
    xpm_t *N;
    xpm_t *S;

    char **c_color;
    char **f_color;


    

    mlx_t    *mlx;
    mlx_image_t *mini;

    double  face_up;
    double  face_down;
    double  face_left;
    double  face_right;
    
}   t_tools;


/*p-5*/

int	is_valid_map(t_tools *itms);
void	open_image(char *path, t_tools *itm, mlx_image_t *img);
int	check_texture_1(char *s, t_tools *itms, void **p);


/*p-4*/

int     check_items(t_tools *itms);
int     is_valid(char *s, t_tools *all);
int     valid_edge(int i, int j, char **s);
int     is_valid_2(char c, t_tools *itms, int i, int j);

/*p-3*/
int     check(char *s, t_tools *all);
void	get_yx(t_tools *itms);
void	ft_hash(char *s, t_tools itms);
int     update_map(t_tools *itms, int cp);

/*p-2*/
int is_empty(char *s);
int check_extention(char *s);
void	ft_init(t_tools *itms);
int	ft_read_map(char *name, t_tools *itms);
char	**update(char **s, char *line);

int is_digit(char c);
void function(char **s);
int	check_texture_2(char *s, t_tools *itms, char c);
int	parssing(char *s, t_tools *itms);

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *str, char c);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
int     ft_strncmp(char *s1, char *s2, int c);
char	**free_2d(char **tbl);

int     ft_strncmp(char *s1, char *s2, int c);


// void draw_map(t_tools *itms);



// void draw_line(t_tools *itm, double end_y, double end_x);
// void dda(t_tools *itm, int p_x , int p_y , int x2, int y2);


#endif