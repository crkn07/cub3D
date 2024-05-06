/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:52:28 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/06 13:55:18 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		game->textwally = game->y_axys - game->textwally - 1;
	if (game->hit_side == 1 && game->rays.x < 0)
		game->textwally = game->y_axys - game->textwally - 1;		
}

void ft_rotate(t_game *game, int turn_dir, double rotation_speed)
{
	double aux;
	double plane_aux;

	game->turn_dir = turn_dir;
	game->rotation = game->rotation + game->turn_dir
		* (rotation_speed * 180 / M_PI);
	aux = game->dir.x;
	game->dir.x = game->dir.x * cos(-rotation_speed) - game->dir.y
		* sin(-rotation_speed);
	game->dir.y = aux * sin(-rotation_speed) + game->dir.y
		* cos(-rotation_speed);
	plane_aux = game->plane.x;
	game->plane.x = game->plane.x * cos(-rotation_speed) - game->plane.y
		* sin(-rotation_speed);
	game->plane.y = plane_aux * sin(-rotation_speed) + game->plane.y
		* cos(-rotation_speed);
}

void	ft_movement(t_game *game, int key, double speed)
{
	double dx;
	double dy;
	
	dx = 0;
	dy = 0;
	if (key == KEY_W || key == KEY_S)
	{
		dx = game->dir.x * speed;
		dy = game->dir.y * speed;
	}
	else if (key == KEY_D || key == KEY_A)
	{
		dx = game->plane.x * speed;
		dy = game->plane.y * speed;
	}
	if (game->map[(int)(game->vect.x + dx)][(int)game->vect.y] == 0)
		game->vect.x += dx;
	if (game->map[(int)game->vect.x][(int)(game->vect.y + dy)] == 0)
		game->vect.y += dy;
}

int	ft_raycast_movements(t_game *game)
{
	if (game->move_keys == KEY_W)
		ft_movement(game, KEY_W, SPEED);
	if (game->move_keys == KEY_S)
		ft_movement(game, KEY_S, -SPEED);
	if (game->side_keys == KEY_D)
		ft_movement(game, KEY_D, SPEED);
	if (game->side_keys == KEY_A)
		ft_movement(game, KEY_A, -SPEED);
	if (game->rotate_keys == KEY_RIGHT)
		ft_rotate(game, 1, ROTATIONSPEED);
	if (game->rotate_keys == KEY_LEFT)
		ft_rotate(game, -1, -ROTATIONSPEED);
	return (0);
}

int	ft_raycasting(t_game *game)
{
	int	i;
	
	i = 0;
	ft_raycast_movements(game);
	while (i < W_WIDTH)
	{
		game->vision = 2.0 * i / (double)W_WIDTH - 1;
		game->rays.x = game->dir.x + game->plane.x * game->vision;
		game->rays.y = game->dir.y + game->plane.y * game->vision;
		ft_algorithm(game);
		game->line_height = (int)(W_HEIGHT / game->pp_to_wall);
		game->d_start = (int)(-game->line_height / 2.0) + (int)(W_HEIGHT / 2.0);
		if (game->d_start < 0)
			game->d_start = 0;
		game->d_end = (int)(game->line_height / 2.0) + (int)(W_HEIGHT / 2.0);
		if (game->d_end >= W_HEIGHT)
			game->d_end = W_HEIGHT - 1;
		ft_ray_line(game, i);
		update_textures(game, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
