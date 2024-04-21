/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/04/21 10:58:18 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define WIDTH 512
#define HEIGHT 512


int main(void)
{
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	
	if (!mlx)
		return (printf("ERROR initializing MLX\n"));
	mlx_image_t *img = mlx_new_image(mlx, 512, 512);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (printf("ERROR initializing MLX\n"));

	mlx_put_pixel(img, HEIGHT / 2, WIDTH / 2, 0xFFFFFFFF);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}