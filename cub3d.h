/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:46:51 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/05/10 11:29:07 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
 
# define CUB3D_H

# define WIDTH 720
# define HEIGHT 720
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define UNIT (WIDTH / MAP_WIDTH)
# define DEG_TO_RAD (M_PI / 180)
# define MAX_CHECK UNIT

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
}	t_vector;

typedef struct s_config
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int 		map[MAP_WIDTH][MAP_HEIGHT];
	t_vector 	player;
	t_vector 	dir;
	t_vector	plane;
	float 		viewAngle;
	float 		fovAngle;
	int 		move_forward;
	int 		move_backward;
	int 		move_right;
	int 		move_left;
	int 		rotate_right;
	int 		rotate_left;
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
t_vector dda_casting(t_config *config, float alpha);

// utils
int in_range(int p, int min, int max);
float normalize_angle(float angle);
void normalize_vector(t_vector *vec);
void draw_point(t_config *config, int x, int y);

#endif