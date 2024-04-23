/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:54:35 by crtorres          #+#    #+#             */
/*   Updated: 2024/03/21 12:57:40 by crtorres         ###   ########.fr       */
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
		game->dis_wall.x = (game->vect.x - game->mapx) * game->distance.x;
	}
	else
		game->dis_wall.x = (game->vect.x + 1.0 - game->mapx) * game->distance.x;
	game->stepy = 1;
	if (game->rays.y < 0)
	{
		game->stepy = game->stepy * -1;
		game->dis_wall.y = (game->vect.y - game->mapy) * game->distance.y;
	}
	else
		game->dis_wall.y = (game->vect.y + 1.0 - game->mapy) * game->distance.y;
	flag = 0;
	while (!flag)
	{
		if (game->dis_wall.x < game->dis_wall.y)
		{
			game->dis_wall.x = game->distance.x;
			game->mapx = game->stepx;
			game->hit_side = X;
		}
		else
		{
			game->dis_wall.y += game->distance.y;
			game->mapy = game->stepy;
			game->hit_side = Y;
		}
		if (game->map[game->mapx][game->mapy] == 1)
			flag = 1;	
	}
	if (game->hit_side == X)
		game->pp_to_wall = game->dis_wall.x - game->distance.x;
	if (game->hit_side == Y)
		game->pp_to_wall = game->dis_wall.y - game->distance.y;
}

void	ft_ray_line(t_game *game, int i)
{
	int j;

	j = -1;
	while (++j < game->d_start)
		game->address[j * W_WIDTH + i] = game->c;
	while (++j < W_HEIGHT)
		game->address[j * W_WIDTH + 1] = game->f;
}

void	update_textures(t_game *game, int i)
{
	double	step;
	int		color;
	int		j;

	color = 0;
	j = 0;
	while (game->e_img)
}