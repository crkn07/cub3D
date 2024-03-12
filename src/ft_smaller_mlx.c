/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smaller_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:49:24 by crtorres          #+#    #+#             */
/*   Updated: 2024/03/12 15:58:57 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*init_img(t_game *game, char *path)
{
	t_img	*img;
	
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
	{
		printf("primer if\n");
		free(path);
		error_message("XPM memory allocation fail\n");
	}
	img->ptr = mlx_xpm_file_to_image(game->mlx, path, &game->x_axys, &game->y_axys);
	printf("x es %d\n", game->x_axys);
	printf("y es %d\n", game->y_axys);
	printf("path es %s\n", path);
	if (img->ptr == NULL)
	{
		printf("segundo if\n");
		//free (path);
		error_message("XPM to image fail! please check it.\n");
	}
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bits, &img->len, &img->endian);
	if(!img->data)
	{
		printf("tercer if\n");
		free(path);
		error_message("XPM data fail! please check it.\n");
	}
	return (img);
}
