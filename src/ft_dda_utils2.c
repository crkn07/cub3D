/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:12:45 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/06 14:29:05 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double player_distance(double ray)
{
	if (ray != 0)
		return fabs(1.0 / ray);
	else
		return 1e30;
}

void ft_wall_dist(t_game *game)
{
	game->stepx = 1;
	if (game->rays.x < 0)
	{
		game->stepx = game->stepx * -1;
		game->dis_wall.x = (game->vect.x - game->mapx) * game->distance.x;
	}
	else
		game->dis_wall.x = (game->mapx + 1.0 - game->vect.x) * game->distance.x;
	game->stepy = 1;
	if (game->rays.y < 0)
	{
		game->stepy = game->stepy * -1;
		game->dis_wall.y = (game->vect.y - game->mapy) * game->distance.y;
	}
	else
		game->dis_wall.y = (game->mapy + 1.0 - game->vect.y) * game->distance.y;
}
