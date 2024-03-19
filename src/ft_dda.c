/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:54:35 by crtorres          #+#    #+#             */
/*   Updated: 2024/03/18 16:22:11 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_algorithm(t_game *game)
{
	int	flag;

	game->mapx = (int)game->vect.x;
	game->mapy = (int)game->vect.y;
	game->distance.x = 1e30;
	if (game->distance.x != 0)
		game->distance.x = fabs(1.0 / game->rays.x);
	game->distance.y = 1e30;
	if (game->distance.y != 0)
		game->distance.y = fabs(1.0 / game->rays.y);
	game->stepx = 1;
	if (game->rays.x < 0)
	{
		game->stepx = game->stepx * -1;
		
	}
}