/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/15 14:30:45 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wtf(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_tools		items;

	atexit(wtf);
	if (argc != 2)
		exit(printf("Invalid args\n"));
	printf("Parsing....\n");
	parssing(argv[1], &items);
	printf("Raycasting....\n");
	config.items = &items;
	init_game(&config, &items);
	draw_map(&config);
	if (config.fail)
	{
		free_config(&config);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(config.mlx, (mlx_keyfunc) handle_click, &config);
	mlx_cursor_hook(config.mlx, (mlx_cursorfunc) handle_mouse, &config);
	mlx_loop_hook(config.mlx, (void *) loop_hook, &config);
	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
	free_config(&config);
	exit(EXIT_SUCCESS);
}
