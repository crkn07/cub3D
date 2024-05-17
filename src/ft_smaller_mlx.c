/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smaller_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:49:24 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/17 15:59:10 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	init_img(t_game *game, char *path)
{
	game->img_data.ptr = mlx_xpm_file_to_image(game->mlx, path,
			&game->x_axys, &game->y_axys);
	if (game->img_data.ptr == NULL)
		error_message("XPM to image fail! please check it.\n");
	game->img_data.data = (int *)mlx_get_data_addr(game->img_data.ptr,
			&game->img_data.bits, &game->img_data.len, &game->img_data.endian);
	if (!game->img_data.data)
		error_message("XPM data fail! please check it.\n");
	return (game->img_data);
}
