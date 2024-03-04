/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:45:04 by crtorres          #+#    #+#             */
/*   Updated: 2024/03/04 17:34:59 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
}

int	check_extension(char *str, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(str) - ft_strlen(ext);
	if (i <= 0 || str[i] != '.')
		error_message("invalid extension\n");
	j = 0;
	while (str[i + j] != '\0' && ext[j] != '\0')
	{
		if (str[i + j] == ext[j])
			j++;
		else
			break ;
	}
	if (!(str[i + j] == '\0' && ext[j] == '\0'))
		error_message("invalid extension\n");
	return (TRUE);
}

void	alloc_map_mem(t_game *game)
{
	int	i;

	game->map = (char **)ft_calloc((game->rows_map), sizeof(char *));
	i = -1;
	while (++i < game->rows_map)
		game->map[i] = ft_calloc((game->cols_map), sizeof(char));
}

void	ft_check_comp(t_game *game)
{
	int	i;
	int	count_element;
	
	count_element = 0;
	i = -1;
	while (game->line[++i])
	{
		if (game->line[i] == 'N' || game->line[i] == 'S' || game->line[i] == 'E' || game->line[i] == 'W')
		{
			game->coord = game->line[i];
			game->vect.x = (i / game->cols_map) + 0.25;
			game->vect.y = (i % game->cols_map) - (i / game->cols_map) + 0.25;
			if (game->coord == 'N')
			{
				game->dir.x = -1;
				game->dir.y = 0;
				game->plane.x = 0;
				game->plane.y = 0.66;
				game->rotation = 180;
			}
			else if (game->coord == 'S')
			{
				game->dir.x = 1;
				game->dir.y = 0;
				game->plane.x = 0;
				game->plane.y = -0.66;
				game->rotation = 0;
			}
			else if (game->coord == 'E')
			{
				game->dir.x = 0;
				game->dir.y = 1;
				game->plane.x = 0.66;
				game->plane.y = 0;
				game->rotation = 90;
			}
			else if (game->coord == 'W')
			{
				game->dir.x = 0;
				game->dir.y = -1;
				game->plane.x = -0.66;
				game->plane.y = 0;
				game->rotation = 270;	
			}
			count_element = 1;
		}
		else if (game->line[i] != 'N' || game->line[i] != 'S' || game->line[i] != 'E' || game->line[i] != 'W' || game->line[i] != ' ' || game->line[i] != '\n' || game->line[i] != '1' || game->line[i] != '0')
			error_message("invalid data\n");
	}
	if (count_element != 1)
			error_message("Invalid or missing components in map\n");
}

void	ft_check_borders(t_game *game)
{
	int	i;

	i = 0;
	while (game->line[i] && game->line[i] != game->coord)
		i++;
	alloc_map_mem(game);
	game->map[(i / game->cols_map)][(i % game->cols_map) - (i / game->cols_map)] = 0;
	if (game->line[i] && game->line[i] == game->coord)
	{
		if ((0 < (i + 1)) && (i + 1 <= game->size) && game->line[i + 1] == '0')
			fill(game, game->size, i + 1, game->cols_map + 1);
		else if ((0 < (i - 1)) && (i - 1 <= game->size) && game->line[i - 1] == '0')
			fill(game, game->size, i - 1, game->cols_map + 1);
		else if ((0 < (i + game->cols_map)) && (i + game->cols_map <= game->size) && game->line[i + game->cols_map] == '0')
			fill(game, game->size, i + game->cols_map, game->cols_map + 1);
		else if ((0 < (i - 1)) && (i - game->cols_map <= game->size) && game->line[i - game->cols_map] == '0')
			fill(game, game->size, i - game->cols_map, game->cols_map + 1);
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (perror("invalid number of arguments"), 1);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (perror("Memory allocation memory"), 1);
	check_extension(argv[1], MAP_EXT);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT, "cub3d");
	if (!game->win)
		error_message("launch_window failed\n");
	ft_read_file(game, argv[1]);
	ft_process_map(game);
	ft_check_textures(game);
	ft_check_comp(game);
	ft_check_borders(game);
	return (0);
}
