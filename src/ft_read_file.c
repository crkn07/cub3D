/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:28:09 by crtorres          #+#    #+#             */
/*   Updated: 2024/03/12 15:39:47 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	int		readed;

	buf = ft_calloc(sizeof(char), 2);
	if (!buf)
		return (NULL);
	readed = 1;
	while (readed != 0)
	{
		readed = read(fd, buf, 1);
		if (readed < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[readed] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
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

unsigned int	ft_print_color(unsigned int *num)
{
	unsigned int	c_code;

	c_code = 0;
	if (!num)
		return (0);
	c_code = (num[0] << 16) | (num[1] << 8) | num[2];
	if (c_code > 16777215)
	{
		free (num);
		error_message("invalid color\n");
	}
	return (c_code);
}

void	ft_check_textures(t_game *game)
{
	int	i;
	int	j;
	unsigned int	*k;
	char *path;
	char **aux;

	i = -1;
	while (game->data_map && game->data_map[++i])
	{
		j = 0;
		if (ft_strcmp(&game->data_map[i][j], " "))
			skip_spaces(game->data_map[i], &j);
		if (game->data_map[i][j] && (game->data_map[i][j] == 'N' && game->data_map[i][j + 1] == 'O' && game->data_map[i][j + 2] == ' '))
		{
			path = ft_strstr(game->data_map[i], "./textures/");
			ft_check_access(path);
			game->n_img = init_img(game, path);
		}
		else if (game->data_map[i][j] && (game->data_map[i][j] == 'S' && game->data_map[i][j + 1] == 'O' && game->data_map[i][j + 2] == ' '))
		{
			path = ft_strstr(game->data_map[i], "./textures/");
			//!ft_check_access(path);
			//game->s_img = init_img(game, path);
		}
		else if (game->data_map[i][j] && (game->data_map[i][j] == 'W' && game->data_map[i][j + 1] == 'E' && game->data_map[i][j + 2] == ' '))
		{
			path = ft_strstr(game->data_map[i], "./textures/");
			//!ft_check_access(path);
			//game->e_img = init_img(game, path);
		}
		else if (game->data_map[i][j] && (game->data_map[i][j] == 'E' && game->data_map[i][j + 1] == 'A' && game->data_map[i][j + 2] == ' '))
		{
			path = ft_strstr(game->data_map[i], "./textures/");
			//!ft_check_access(path);
			//game->w_img = init_img(game, path);
		}
		else if (game->data_map[i][j] && (game->data_map[i][j] == 'F' && game->data_map[i][j + 1] == ' '))
		{
			j++;
			if (ft_strcmp(&game->data_map[i][j], " ") != 0)
				skip_spaces(game->data_map[i], &j);
			path = ft_strdup(&game->data_map[i][j]);
			aux = ft_split(path, ',');
			k = ft_ctoascii(aux);
			free(path);
			game->f = ft_print_color(k);
			free (k);
		}
		else if (game->data_map[i][j] && (game->data_map[i][j] == 'C' && game->data_map[i][j + 1] == ' '))
		{
			j++;
			if (ft_strcmp(&game->data_map[i][j], " ") != 0)
				skip_spaces(game->data_map[i], &j);
			path = ft_strdup(&game->data_map[i][j]);
			aux = ft_split(path, ',');
			k = ft_ctoascii(aux);
			free(path);
			game->c = ft_print_color(k);
			free (k);
		}
		/* else
			error_message("invalid data in map coord\n"); */
	}
	/* if (!game->n_img || !game->s_img || !game->w_img || !game->e_img)
		error_message("invalid data\n"); */
}

void	ft_read_file(t_game *game, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message("error opening file, check filename or file path\n");
	game->map_file = ft_calloc(sizeof(char), 1);
	if (!game->map_file)
		exit (EXIT_FAILURE);
	game->map_file = read_and_stash(fd, game->map_file);
	close(fd);
}
