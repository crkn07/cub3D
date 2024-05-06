/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:50:20 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/06 13:59:26 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	alloc_map_mem(t_game *game)
{
	int	i;
	int	j = 0;
	int	k;
	
	game->map = (int **)ft_calloc((game->rows_map), sizeof(int *));
	i = -1;
	while (++i < game->rows_map)
	{
		game->map[i] = ft_calloc((game->cols_map), sizeof(int));
		k = -1;
		while (game->line[j] && game->line[j] != '\n')
		{
			if (game->line[j] == '0' || game->line[j] == '1')
				game->map[i][++k] = game->line[j] - 48;
			else
				game->map[i][++k] = -1;
			j++;	
		}
		j++;	
	}
}

int	check_extension(char *str, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(str) - ft_strlen(ext);
	if (i <= 0 || str[i] != '.')
		error_message("invalid extension\n");
	j = 0;
	while (str[i + j] != '\0' && ext[j] != '\0')
	{
		if (str[i + j] == ext[j])
			j++;
		else
			break ;
	}
	if (!(str[i + j] == '\0' && ext[j] == '\0'))
		error_message("invalid extension\n");
	return (TRUE);
}

void	ft_check_textures(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->d_map && game->d_map[++i])
	{
		j = 0;
		if (ft_strcmp(&game->d_map[i][j], " "))
			skip_spaces(game->d_map[i], &j);
		ft_load_texture(game, i, j, "NO");
		ft_load_texture(game, i, j, "SO");
		ft_load_texture(game, i, j, "WE");
		ft_load_texture(game, i, j, "EA");
		ft_load_color(game, i, &j, 'F');
		ft_load_color(game, i, &j, 'C');
		/* else
			error_message("invalid data in map coord\n"); */
	}
	if (!game->n_img || !game->s_img || !game->w_img || !game->e_img)
		error_message("invalid data\n");
}

unsigned int	*ft_ctoascii(char **num)
{
	unsigned int	*n;
	int				i;

	i = -1;
	n = calloc(sizeof(int), 4);
	if (!n)
	{
		free_mtx(num);
		error_message("problem whith numbers");
	}
	while (num[++i])
	{
		n[i] = ft_atoi(num[i]);
		if (n[i] < 0 || n[i] > 255)
		{
			free(n);
			free_mtx(num);
			error_message("problem whith numbers");
		}
	}
	free_mtx(num);
	return (n);
}
