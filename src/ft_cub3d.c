/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:45:04 by crtorres          #+#    #+#             */
/*   Updated: 2024/03/11 17:22:00 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	//free_mtx(&game->line);
	exit(EXIT_SUCCESS);
}

void	alloc_map_mem(t_game *game)
{
	int	i;

	game->map = (char **)ft_calloc((game->rows_map), sizeof(char *));
	i = -1;
	while (++i < game->rows_map)
		game->map[i] = ft_calloc((game->cols_map), sizeof(char));
}

void	ft_init_game(t_game *game)
{
	game->win = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "cub3d");
	if (!game->win)
		error_message("launch_window failed\n");
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!game->img)
		error_message("launch_window image failed\n");
	game->address = (int *)mlx_get_data_addr(game->img, &game->bitpp, \
			&game->lengh_line, &game->endian);
	game->move_keys = -1;
	game->rotate_keys = -1;
	game->turn_dir = -1;
}

/* int	ft_raycasting(void *pointer)
{
	t_game	*game;
	int i;
	
	i = 0;
	game = (void *)pointer;
	
} */
void	ft_leaks(void)
{
	system("leaks -q cub3d");
}

int	main(int argc, char **argv)
{
	t_game	*game;

	atexit(ft_leaks);
	if (argc != 2)
		return (perror("invalid number of arguments"), 1);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (perror("Memory allocation memory"), 1);
	check_extension(argv[1], MAP_EXT);
	game->mlx = mlx_init();
	ft_read_file(game, argv[1]);
	ft_process_map(game);
	ft_check_textures(game);
	ft_check_comp(game);
	ft_check_borders(game);
	ft_init_game(game);
	mlx_hook(game->win, KEY_EXIT, 0, &close_game, game);
	mlx_hook(game->win, KEY_PRESS, 0, &keypress, game);
	mlx_hook(game->win, KEY_PRESS, 0, &key_release, game);
	mlx_loop(game->mlx);
	return (0);
}
