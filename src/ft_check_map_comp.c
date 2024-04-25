/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_comp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:12:20 by crtorres          #+#    #+#             */
/*   Updated: 2024/04/25 14:50:34 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			g->coord = g->line[i];
			g->vect.x = (i / g->cols_map) + 0.25;
			g->vect.y = (i % g->cols_map) - (i / g->cols_map) + 0.25;
			printf("cols es %f\n", g->vect.y);
			if (g->coord == 'N' || g->coord == 'S')
				ft_check_north_south(g);
			if (g->coord == 'E' || g->coord == 'W')
				ft_check_east_weast(g);
			count_element = 1;
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
	//printf("row es %d e i es %d\n", game->cols_map, i);
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