/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:45:04 by crtorres          #+#    #+#             */
/*   Updated: 2024/08/23 12:25:20 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = -1;
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->map)
	{
		while (++i < game->rows_map)
			free(game->map[i]);
		free(game->map);
		game->map = NULL;
	}
	if (game->d_map)
		free_mtx(game->d_map);
	if (game->map_file)
		free(game->map_file);
	if (game->line)
		free(game->line);
}

int	close_game(t_game *game)
{
	if (game->img)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	free_game(game);
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

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (perror("invalid number of arguments"), 1);
	bzero(&game, sizeof(t_game));
	check_extension(argv[1], MAP_EXT);
	game.mlx = mlx_init();
	ft_read_file(&game, argv[1]);
	ft_process_map(&game);
	ft_check_textures(&game);
	ft_check_comp(&game);
	ft_check_borders(&game);
	ft_init_game(&game);
	ft_raycasting(&game);
	mlx_hook(game.win, KEY_EXIT, (1L << 0), &close_game, &game);
	mlx_hook(game.win, KEY_PRESS, (1L << 0), &keypress, &game);
	mlx_hook(game.win, KEY_RELEASE, (1L << 1), &key_release, &game);
	mlx_loop_hook(game.mlx, &ft_raycasting, &game);
	mlx_loop(game.mlx);
	return (0);
}
