/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:46:51 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/22 15:45:01 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
 
# define CUB3D_H

# define WIDTH 720
# define HEIGHT 720
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# include "./lib/MLX/include/MLX42/MLX42.h"

typedef struct s_config
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int map[MAP_WIDTH][MAP_HEIGHT];
	int xPos;
	int yPos;
}	t_config;


// draw
void draw_map(t_config *config);

// hooks
void move_player(mlx_key_data_t keydata, t_config *config);

#endif