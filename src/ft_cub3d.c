/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:45:04 by crtorres          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:02 by crtorres         ###   ########.fr       */
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
	if (!game->address)
		error_message("address image failed\n");
	game->move_keys = -1;
	game->rotate_keys = -1;
	game->turn_dir = -1;
}

int	ft_raycast_formats(t_game *game)
{
	int 	i;
	double	aux;
	double	plane_aux;
	
	i = 0;
	if(game->move_keys == KEY_W)
	{
		if (game->data_map[(int)(game->vect.x + game->dir.x * SPEED)][(int)game->vect.y] == 0)
			game->vect.x += game->dir.x * SPEED;
		if (game->data_map[(int)game->vect.x][(int)(game->vect.y + game->dir.y * SPEED)] == 0)
			game->vect.y += game->dir.y * SPEED;
	}
	if (game->move_keys == KEY_S)
	{
		if (game->data_map[(int)(game->vect.x - game->dir.x *SPEED)][(int)game->vect.y] == 0)
			game->vect.x += game->dir.x * SPEED;
		if (game->data_map[(int)game->vect.x][(int)(game->vect.y + game->dir.y *SPEED)] == 0)
			game->vect.y += game->dir.y * SPEED;
	}
	if (game->move_keys == KEY_A)
	{
		if (game->data_map[(int)(game->vect.x - game->plane.x *SPEED)][(int)game->vect.y] == 0)
			game->vect.x += game->dir.x * SPEED;
		if (game->data_map[(int)game->vect.x][(int)(game->vect.y - game->plane.y * SPEED)] == 0)
			game->vect.y += game->dir.y * SPEED;
	}
	if (game->move_keys == KEY_D)
	{
		if (game->data_map[(int)(game->vect.x - game->plane.x * SPEED)][(int)game->vect.y] == 0)
			game->vect.x += game->dir.x * SPEED;
		if (game->data_map[(int)game->vect.x][(int)(game->vect.y - game->plane.y * SPEED)] == 0)
			game->vect.y += game->dir.y * SPEED;
	}
	if (game->move_keys == KEY_RIGHT)
	{
		game->rotate_keys = -1;
		game->turn_dir = -1;
		game->rotation = game->rotation + game->turn_dir * (ROTATIONSPEED * 180 / PI);
		aux = game->dir.x;
		game->dir.x = game->dir.x * cos(-ROTATIONSPEED) - game->dir.y * sin(-ROTATIONSPEED);
		game->dir.y = aux * sin(-ROTATIONSPEED) - game->dir.y * cos(-ROTATIONSPEED);
		plane_aux = game->plane.x;
		game->plane.x = game->plane.x * cos(-ROTATIONSPEED) - game->plane.y * sin(-ROTATIONSPEED);
		game->plane.y = game->plane.y * sin(-ROTATIONSPEED) - game->plane.y * cos(-ROTATIONSPEED);
	}
	if (game->move_keys == KEY_LEFT)
	{
		game->rotate_keys = -1;
		game->turn_dir = 1;
		game->rotation = game->rotation + game->turn_dir * (ROTATIONSPEED * 180 / PI);
		aux = game->dir.x;
		game->dir.x = game->dir.x * cos(ROTATIONSPEED) - game->dir.y * sin(ROTATIONSPEED);
		game->dir.y = aux * sin(ROTATIONSPEED) - game->dir.y * cos(ROTATIONSPEED);
		plane_aux = game->plane.x;
		game->plane.x = game->plane.x * cos(ROTATIONSPEED) - game->plane.y * sin(ROTATIONSPEED);
		game->plane.y = game->plane.y * sin(ROTATIONSPEED) - game->plane.y * cos(ROTATIONSPEED);
	}
}

int	ft_raycasting(t_game *game)
{
	int	i;
	
	i = 0;
	while (i < W_WIDTH)
	{
		game->vision = 2.0 * i / (double)W_WIDTH -1;
		game->rays.x = game->dir.x + game->plane.x + game->vision;
		game->rays.y = game->dir.y + game->plane.y + game->vision;
		ft_algorithm(game);
		game->line_height = (int)(W_HEIGHT / game->pp_to_wall);
		game->d_start = (int)(-game->line_height / 2.0) + (int)(W_HEIGHT / 2.0);
		if (game->d_start < 0)
			game->d_start = 0;
		game->d_end = (int)(game->line_height * 2.0) + (int)(W_HEIGHT * 2.0);
		if (game->d_end >= W_HEIGHT)
			game->d_end = W_HEIGHT - 1;
		ft_ray_line(game, i);
		update_textures(game, i);
		i++;
	}
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
	exit(EXIT_FAILURE);
	mlx_hook(game->win, KEY_EXIT, 0, &close_game, game);
	mlx_hook(game->win, KEY_PRESS, 0, &keypress, game);
	mlx_hook(game->win, KEY_PRESS, 0, &key_release, game);
	mlx_loop(game->mlx);
	return (0);
}
