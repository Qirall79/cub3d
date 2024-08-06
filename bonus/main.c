/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 08:47:56 by wbelfatm          #+#    #+#             */
/*   Updated: 2024/08/06 10:39:12 by wbelfatm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void wtf(void)
{
	system("leaks cub3d");
}

int my_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return i;
}

int **get_map(char **map_lines, t_config *config)
{
	int size = 0;
	int i;
	int j;
	int **res;
	int *row;

	while (map_lines[size])
		size++;
	res = (int **) malloc(sizeof(int *) * (size + 1));
	i = 0;
	while (i < size)
	{
		j = 0;
		row = (int *) malloc(sizeof(int) * (my_strlen(map_lines[i]) - 1));
		while (map_lines[i][j] && map_lines[i][j] != '\n')
		{
			if (map_lines[i][j] == 'N' || map_lines[i][j] == 'S'
			|| map_lines[i][j] == 'W' || map_lines[i][j] == 'E')
			{
				row[j] = 5;
				config->orientation = map_lines[i][j];
			}
			else if (map_lines[i][j] == 'D')
				row[j] = 4;
			else if (map_lines[i][j] == 'O')
				row[j] = 6;
			else if (map_lines[i][j] == 'T')
				row[j] = 2;
			else if (map_lines[i][j] == 'C')
				row[j] = 3;
			else if (map_lines[i][j] == '1')
				row[j] = 1;
			else
				row[j] = 0;
			j++;
		}
		res[i] = row;
		i++;
	}
	res[i] = NULL;
	return res;
}

int	main(int argc, char **argv)
{
	// atexit(wtf);
	t_config config;
	t_tools items;

	if (argc != 2)
		exit(printf("Invalid args\n"));
	parssing(argv[1], &items);

	int **map = get_map(items.maps, &config);
	
	int i = 0;
	int width = my_strlen(items.maps[0]) - 1;
	while (items.maps[i])
	{
		i++;
	}


	config.path_n = items.path_NO;
	config.path_e = items.path_EA;
	config.path_w = items.path_WE;
	config.path_s = items.path_SO;
	config.map = map;
	config.map_width = width;
	config.map_height = i;
	init_game(&config);
	draw_map(&config);

	// hooks
	mlx_key_hook(config.mlx, (mlx_keyfunc) handle_click, &config);
	mlx_cursor_hook(config.mlx, (mlx_cursorfunc) handle_mouse, &config);
	mlx_loop_hook(config.mlx, (void *) loop_hook, &config);

	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
	free_config(&config);
	return (EXIT_SUCCESS);
}
