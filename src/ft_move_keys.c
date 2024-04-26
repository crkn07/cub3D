/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:19:19 by crtorres          #+#    #+#             */
/*   Updated: 2024/04/26 15:36:13 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	keypress(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		game->move_keys = keycode;
	else if (keycode == KEY_A || keycode == KEY_D)
		game->side_keys = keycode;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		game->move_keys = keycode;
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		game->rotate_keys = keycode;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_message("game finished", game);
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
	{
		game->turn_dir = 0;
		game->rotate_keys = -1;
	}
	if (keycode == KEY_W || keycode == KEY_S)
		game->move_keys = -1;
	if (keycode == KEY_D || keycode == KEY_A)
		game->side_keys = -1;
	return (0);
}
