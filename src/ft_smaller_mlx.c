/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smaller_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:49:24 by crtorres          #+#    #+#             */
/*   Updated: 2024/04/24 16:41:08 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*init_img(t_game *game, char *path)
{
	t_img	*img;
	
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
	{
		free(path);
		error_message("XPM memory allocation fail\n");
	}
	img->ptr = mlx_xpm_file_to_image(game->mlx, path, &game->x_axys, &game->y_axys);
	if (img->ptr == NULL)
	{
		//free (path);
		printf("path es %s\n", path);
		error_message("XPM to image fail! please check it.\n");
	}
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bits, &img->len, &img->endian);
	if(!img->data)
	{
		free(path);
		error_message("XPM data fail! please check it.\n");
	}
	return (img);
}
