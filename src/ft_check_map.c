/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:37:40 by crtorres          #+#    #+#             */
/*   Updated: 2024/03/11 17:17:51 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_start_map(t_game *game, char **map_data)
{
	int		i;
	int		j;
	int		y;

	i = -1;
	y = ft_strlen(map_data[6]);
	while (game->map_file[++i])
	{
		j = 0;
		while (map_data[6][j] == game->map_file[i])
		{
			i++;
			j++;
			if (y == j)
				return (i + 1);
		}
	}
	return (i);
}

void	ft_add_space(t_game *game, int i)
{
	while (i < game->cols_map)
	{
		game->line = ft_strjoin(game->line, " ");
		i++;
	}
}

void	ft_process_data_map(t_game *game, char **str, int start)
{
	int	i;

	game->line = ft_strdup(str[6]);
	ft_add_space(game, ft_strlen(str[6]));
	i = 7;
	while (str && str[i] && i < game->cols_map)
	{
		game->line = ft_strjoin(game->line, "\n");
		if (game->map_file[start] && (ft_strcmp(&game->map_file[start], "\n") == 0))
		{
			ft_add_space(game, 0);
			start++;
		}
		else
		{
			game->line = ft_strjoin(game->line, str[i]);
			ft_add_space(game, ft_strlen(str[i]));
			start = start + 1 + ft_strlen(str[i]);
		}
		i++;
	}
	game->size = ft_strlen(game->line);
}

void	num_max_rowsandcols(t_game *game, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->cols_map = 0;
	game->rows_map = 0;
	while (line[i])
	{
		if (!line[i + 1] || line[i + 1] == '\n')
		{
			if (j > game->cols_map)
				game->cols_map = j;
			game->rows_map += 1;
			j = 0;
		}
		else
			j++;
		i++;
	}
}


void	ft_process_map(t_game *game)
{
	char	**line_sp;
	char	*line;
	int		i;
	int		start;

	line_sp = ft_split(game->map_file, '\n');
	if (!line_sp || !line_sp[5] || !line_sp[6])
		error_message("ERROR procces");
	game->data_map = ft_split(game->map_file, '\n');
	i = 6;
	line = ft_strdup(line_sp[6]);
	while (line_sp[++i])
	{
		line = ft_strjoin(line, "\n");
		line = ft_strjoin(line, line_sp[i]);
	}
	num_max_rowsandcols(game, line);
	start = ft_check_start_map(game, line_sp);
	free(line);
	ft_process_data_map(game, line_sp, start);
	free_mtx(line_sp);
}
