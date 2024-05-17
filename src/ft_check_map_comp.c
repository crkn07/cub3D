/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_comp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:12:20 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/16 13:44:30 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_north_south(t_game *game)
{
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
}

void	ft_check_east_weast(t_game *game)
{
	if (game->coord == 'E')
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
}

void	update_coord(t_game *game, int i)
{
	game->coord = game->line[i];
	game->vect.x = (i / game->cols_map) + 0.25;
	game->vect.y = (i % game->cols_map) - (i / game->cols_map) + 0.25;
}

void	ft_check_comp(t_game *g)
{
	int	i;
	int	count_element;

	count_element = 0;
	i = -1;
	while (g->line[++i])
	{
		if (g->line[i] == 'N' || g->line[i] == 'S' || g->line[i] == 'E'
			|| g->line[i] == 'W')
		{
			update_coord(g, i);
			if (g->coord == 'N' || g->coord == 'S')
				ft_check_north_south(g);
			if (g->coord == 'E' || g->coord == 'W')
				ft_check_east_weast(g);
			count_element += 1;
		}
		else if (g->line[i] != 'N' && g->line[i] != 'S' && g->line[i] != 'E'
			&& g->line[i] != 'W' && g->line[i] != ' ' && g->line[i] != '\n'
			&& g->line[i] != '1' && g->line[i] != '0')
			error_message("invalid data in check comp\n");
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
	game->map[(i / game->cols_map)]
	[(i % game->cols_map) - (i / game->cols_map)] = 0;
	if (game->line[i] && game->line[i] == game->coord)
	{
		if ((0 < (i + 1)) && (i + 1 <= game->size) && game->line[i + 1] == '0')
			fill(game, game->size, i + 1, game->cols_map + 1);
		else if ((0 < (i - 1)) && (i - 1 <= game->size)
			&& game->line[i - 1] == '0')
			fill(game, game->size, i - 1, game->cols_map + 1);
		else if ((0 < (i + game->cols_map))
			&& (i + game->cols_map <= game->size)
			&& game->line[i + game->cols_map] == '0')
			fill(game, game->size, i + game->cols_map, game->cols_map + 1);
		else if ((0 < (i - 1)) && (i - game->cols_map <= game->size)
			&& game->line[i - game->cols_map] == '0')
			fill(game, game->size, i - game->cols_map, game->cols_map + 1);
	}
}
