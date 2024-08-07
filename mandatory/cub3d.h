/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:46:51 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/07 14:19:24 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
 
# define CUB3D_H
 

# define WIDTH 960
# define HEIGHT 840
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define UNIT 64
# define COLLECTIBLE_STEP (UNIT / 32)
# define SUB_UNIT (WIDTH / MAP_WIDTH)
# define MAP_UNIT 16
# define ENEMY_SIZE (UNIT)
# define TEX_WIDTH UNIT
# define TEX_HEIGHT UNIT
# define DEG_TO_RAD (float)(M_PI / 180.0)
# define MAX_CHECK UNIT

// enum should be
# define RIGHT 1
# define DOWN 1
# define TOP 2
# define LEFT 2

// directions
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "./lib/MLX42/include/MLX42/MLX42.h"
# include "parsing.h"

typedef struct s_vector
{
	float x;
	float y;
	float z;
	float distance;
}	t_vector;

typedef struct s_dimensions
{
	int height;
	int width;
}	t_dimensions;


typedef struct s_minimap
{
	int **map;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
}	t_minimap;

typedef struct s_config
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_tools *items;
	int width;
	int height;
	int map_width;
	int map_height;
	int **map;
	int **texture_north;
	int **texture_south;
	int **texture_east;
	int **texture_west;
	char *path_n;
	char *path_s;
	char *path_e;
	char *path_w;
	mlx_texture_t *tex;
	float xPos;
	float yPos;
	int		initial_player_x;
	int		initial_player_y;
	float viewAngle;
	float fovAngle;
	float dirX;
	float dirY;
	int move_forward;
	int move_backward;
	int move_right;
	int move_left;
	int rotate_right;
	int rotate_left;
	int fail;
	char orientation;
	int c_color;
	int f_color;
}	t_config;

typedef struct s_node
{
	int x;
	int y;
	int visited;
	int is_obstacle;
	float local_goal;
	float global_goal;
	struct s_node *parent;
	struct s_node **neighbors;
}	t_node;

// draw
void draw_map(t_config *config);
void redraw_image(t_config *config);
void	draw_line(t_vector start, t_vector end,
t_config *config, int color);
void draw_rays(t_config *config);
void	draw_score(t_config *config);
void	redraw_image(t_config *config);


// hooks
void move_player(t_config *config);
void set_movement_params(mlx_key_data_t keydata, t_config *config);
void handle_click(mlx_key_data_t keydata, t_config *config);
void loop_hook(t_config *config);
void handle_mouse(double xpos, double ypos, t_config *config);
int	is_wall_v(float newX, float newY, t_config *config);
float	normalize_angle(float angle);
int	is_wall_h(float newX, float newY, t_config *config);
int	is_wall_v(float newX, float newY, t_config *config);
void	check_collection(t_config *config);
void	move_forward(t_config *config, float mov_speed);
void	move_backward(t_config *config, float mov_speed);
void	move_right(t_config *config, float mov_speed);
void	move_left(t_config *config, float mov_speed);
void	move_player(t_config *config);
void	display_full(t_config *config, int **texture);
void	handle_click(mlx_key_data_t keydata, t_config *config);
void	end_game(t_config *config);
void	set_movement_params(mlx_key_data_t keydata, t_config *config);
void	handle_mouse(double xpos, double ypos, t_config *config);
void	reset_game(t_config *config);
int	enemy_in_door(t_config *config);
void	rotate(t_config *config, float rot_speed);
void handle_resize(int32_t width, int32_t height, t_config *config);

// raycasting
t_vector find_intersection(t_config *config, float alpha);
int	check_wall_hit(t_config *config, t_vector map_pos);
int	set_params_v(t_config *config, t_vector *a, t_vector *step, float alpha);
int	set_params_h(t_config *config, t_vector *a, t_vector *step, float alpha);

// rendering
void draw_wall(t_config *config, t_vector p, float alpha, int x);
float	get_wall_height(t_config *config, float distance, float alpha);
t_vector	get_map_pos(t_vector p, float alpha);
int	get_color(t_config *config, t_vector p, float alpha, t_vector texture_pos);
int	get_texture_x(t_vector p);

// utils
int in_range(int p, int min, int max);
float normalize_angle(float angle);
void normalize_vector(t_vector *vec);
void draw_point(t_config *config, int x, int y);
int vertical_facing(float angle);
int horizontal_facing(float angle);
float get_distance(float xi, float yi, float xf, float yf);
void free_config(t_config *config);
void set_failure(t_config *config);
uint32_t	abgr_to_rgba(uint32_t abgr_color);
int	**generate_texture(char *path, t_config *config, t_dimensions d);
void	load_texture(t_config *config, char *path);
int	**allocate_texture(t_config *config, t_dimensions d);
int	get_color_index(mlx_texture_t *tex, int x, int y, t_dimensions d);
int	count_sprites(t_config *config);
void	set_dimensions(t_config *config);
int	count_sprites(t_config *config);
void	set_sprites_pos(t_config *config, int index, int i, int j);
void	set_pos(t_config *config);
void	copy_map(t_config *config, int map[MAP_HEIGHT][MAP_WIDTH]);
void	assign_paths(t_config *config);
void	init_game(t_config *config, t_tools *items);
void	init_config(t_config *config);
void	init_sprites_textures(t_config *config);
void	init_screens(t_config *config);
void	set_dimensions(t_config *config);
int	ft_atoi(const char *str);
void free_items(t_tools *items);
void	init_map(t_config *config, t_tools *items);

// parsing
int	parssing(char *s, t_tools *itms);

#endif