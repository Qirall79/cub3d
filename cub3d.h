/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:46:51 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/18 12:07:51 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
 
# define CUB3D_H

# define WIDTH 720
# define HEIGHT 720
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define UNIT 640
# define SUB_UNIT (WIDTH / MAP_WIDTH)
# define MAP_UNIT 8
# define ENEMY_SIZE (UNIT)
# define SPRITE_SIZE 640
# define TEX_WIDTH UNIT
# define TEX_HEIGHT UNIT
# define DEG_TO_RAD (float)(M_PI / 180.0)
# define MAX_CHECK UNIT

// enum should be
# define RIGHT 1
# define DOWN 1
# define TOP 2
# define LEFT 2


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "./lib/MLX/include/MLX42/MLX42.h"

typedef struct s_vector
{
	float x;
	float y;
	float z;
	float distance;
}	t_vector;

typedef struct s_boundary
{
	float start;
	float end;
}	t_boundary;

typedef struct s_sprite
{
	float	distance;
	float	height;
	float	angle;
	float	angle_diff;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
	int		max_offset;
} t_sprite;

typedef struct s_config
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int map[MAP_WIDTH][MAP_HEIGHT];
	int **texture;
	int **texture_north;
	int **texture_south;
	int **texture_east;
	int **texture_west;
	int **sprite;
	mlx_texture_t *tex;
	float xPos;
	float yPos;
	t_vector sprite_pos;
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
	int *rays;
	int		sprite_offset;
	int		flying_up;
}	t_config;



// draw
void draw_map(t_config *config);
void redraw_image(t_config *config);
void draw_line(float yi, float xi, float yf, float xf, t_config *config, int color);
void draw_rays(t_config *config);

// hooks
void move_player(t_config *config);
void set_movement_params(mlx_key_data_t keydata, t_config *config);
void loop_hook(t_config *config);

// raycasting
t_vector find_intersection(t_config *config, float alpha);

// rendering
void draw_wall(t_config *config, t_vector p, float alpha, int x);
void draw_sprite(t_config *config);

// utils
int in_range(int p, int min, int max);
float normalize_angle(float angle);
void normalize_vector(t_vector *vec);
void draw_point(t_config *config, int x, int y);
int vertical_facing(float angle);
int horizontal_facing(float angle);

#endif