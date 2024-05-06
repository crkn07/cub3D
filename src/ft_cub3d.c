/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:45:04 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/06 13:53:55 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	//free_mtx(&game->line);
	exit(EXIT_SUCCESS);
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
	if (!game->address)
		error_message("address image failed\n");
	game->move_keys = -1;
	game->rotate_keys = -1;
	game->turn_dir = -1;
	game->side_keys = -1;
}

/* void	ft_leaks(void)
{
	system("leaks -q cub3d");
} */

int	main(int argc, char **argv)
{
	t_game	*game;

	//atexit(ft_leaks);
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
	ft_raycasting(game);
	mlx_hook(game->win, KEY_EXIT, 0, &close_game, game);
	mlx_hook(game->win, KEY_PRESS, 0, &keypress, game);
	mlx_hook(game->win, KEY_RELEASE, 0, &key_release, game);
	mlx_loop_hook(game->mlx, &ft_raycasting, game);
	mlx_loop(game->mlx);
	return (0);
}
