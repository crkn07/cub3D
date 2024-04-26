/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:54:35 by crtorres          #+#    #+#             */
/*   Updated: 2024/04/26 14:58:09 by crtorres         ###   ########.fr       */
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
			game->dis_wall.x += game->distance.x;
			game->mapx += game->stepx;
			game->hit_side = X;
		}
		else
		{
			game->dis_wall.y += game->distance.y;
			game->mapy += game->stepy;
			game->hit_side = Y;
		}
		if (game->map[game->mapx][game->mapy] == 1)
			flag = 1;
	}
	if (game->hit_side == X)
		game->pp_to_wall = game->dis_wall.x - game->distance.x;
	else
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
int	ft_choose_color(t_game *game)
{
	int	color;

	color = 0;
	if (game->hit_side == 0 && game->rays.x > 0)
		color = *(game->n_img->data + (game->x_axys * game->textwallx + game->textwally));
	if (game->hit_side == 0 && game->rays.x < 0)
		color = *(game->s_img->data + (game->x_axys * game->textwallx + game->textwally));
	if (game->hit_side == 1 && game->rays.y > 0)
		color = *(game->w_img->data + (game->x_axys * game->textwallx + game->textwally));
	if (game->hit_side == 1 && game->rays.y < 0)
		color = *(game->e_img->data + (game->x_axys * game->textwallx + game->textwally));
	return (color);
}

void	ft_data_text(t_game *game)
{
	double	wallx;

	if (game->hit_side == 0)
		wallx = game->vect.y + game->pp_to_wall * game->rays.y;
	else
		wallx = game->vect.x + game->pp_to_wall * game->rays.x;
	wallx -= floor(wallx);
	game->textwally = (int)(wallx * (double)game->y_axys);
	if (game->hit_side == 0 && game->rays.x > 0)
		game->textwally = game->y_axys - game->textwally -1;
	if (game->hit_side == 1 && game->rays.x < 0)
		game->textwally = game->y_axys - game->textwally -1;		
}

void	update_textures(t_game *game, int i)
{
	double	step;
	int		color;
	double	pos;
	int		j;

	color = 0;
	j = 0;
	ft_data_text(game);
	step = 1.0 * game->x_axys / game->line_height;
	pos = (game->d_start - W_HEIGHT / 2 + game->line_height / 2) * step;
	while (j < game->d_end + 1)
	{
		game->textwallx = (int)pos & (game->x_axys - 1);
		pos += step;
		color = ft_choose_color(game);
		if (game->hit_side == 1)
			color = (color >> 1) & 8355711;
		game->address[j * W_WIDTH + i] = color;
		j++;
	}
}
