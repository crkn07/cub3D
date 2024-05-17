/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:28:09 by crtorres          #+#    #+#             */
/*   Updated: 2024/05/17 16:00:45 by crtorres         ###   ########.fr       */
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

void	ft_load_texture(t_game *g, int i, int j, char *dir)
{
	char	*path;
	char	**aux;

	if (g->d_map[i][j]
		&& strncmp(g->d_map[i] + j, dir, 2) == 0 && g->d_map[i][j + 2] == ' ')
	{
		path = ft_strstr(g->d_map[i], "./textures/");
		if (strcmp(dir, "WE") == 0)
		{
			aux = ft_split(path, ' ');
			ft_check_access(*aux);
			g->w_img = init_img(g, *aux);
			free_mtx(aux);
		}
		else
		{
			ft_check_access(path);
			if (strcmp(dir, "NO") == 0)
				g->n_img = init_img(g, path);
			else if (strcmp(dir, "SO") == 0)
				g->s_img = init_img(g, path);
			else if (strcmp(dir, "EA") == 0)
				g->e_img = init_img(g, path);
		}
	}
}

void	ft_load_color(t_game *game, int i, int *j, char color)
{
	char			*path;
	char			**aux;
	unsigned int	*k;

	if (game->d_map[i][*j] && (game->d_map[i][*j] == color
		&& game->d_map[i][*j + 1] == ' '))
	{
		(*j)++;
		if (ft_strcmp(&game->d_map[i][*j], " ") != 0)
			skip_spaces(game->d_map[i], j);
		path = ft_strdup(&game->d_map[i][*j]);
		aux = ft_split(path, ',');
		k = ft_ctoascii(aux);
		free(path);
		if (color == 'F')
			game->f = ft_print_color(k);
		else if (color == 'C')
			game->c = ft_print_color(k);
		free (k);
	}
}

void	ft_read_file(t_game *game, char *file)
{
	int		fd;
	char	*aux;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message("error opening file, check filename or file path\n");
	aux = ft_calloc(sizeof(char), 1);
	if (!aux)
		exit (EXIT_FAILURE);
	game->map_file = read_and_stash(fd, aux);
	if (ft_strlen(game->map_file) < 1
		|| ft_strspn(game->map_file, " \t\n") == ft_strlen(game->map_file))
		error_message("empty map\n");
	close(fd);
}
