/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:12:55 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/06 12:34:16 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_access(char *path)
{
	if (access(path, F_OK) != 0 || access(path, R_OK) != 0)
		error_message(path);
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

void	fill(t_game *game, int size, int current, int col)
{
	if (current < 0 || current > size || (game->line[current] != '0'
		&& game->line[current] != '1' && game->line[current] != '\0'
		&& game->line[current] != 'X'
		&& game->line[current] != game->coord))
		error_message("map is not closed\n");
	if (game->line[current] == '0')
	{
		game->line[current] = 'X';
		fill(game, size, current - 1, col);
		fill(game, size, current + 1, col);
		fill(game, size, current - col, col);
		fill(game, size, current + col, col);
	}
}
