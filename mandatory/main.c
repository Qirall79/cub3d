/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/12 20:43:28 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void wtf()
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	// atexit(wtf);
	t_config	config;
	t_tools		items;

	if (argc != 2)
		exit(printf("Invalid args\n"));
	config.items = &items;
	parssing(argv[1], &items);
	init_game(&config, &items);
	draw_map(&config);
	if (config.fail)
		exit(1);
	mlx_key_hook(config.mlx, (mlx_keyfunc) handle_click, &config);
	mlx_loop_hook(config.mlx, (void *) loop_hook, &config);
	mlx_resize_hook(config.mlx, (mlx_resizefunc) handle_resize, &config);
	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
	free_config(&config);
	// exit (EXIT_SUCCESS);
	return 0;
}
