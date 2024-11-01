/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:43:21 by crtorres          #+#    #+#             */
/*   Updated: 2024/10/30 10:56:35 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "src/libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>
# include <dirent.h>
# include <sys/time.h>
# include <pthread.h>
# include <math.h>

# define MAP_EXT		".cub"

# define W_WIDTH	1920
# define W_HEIGHT	1080

# define FALSE		0
# define TRUE		1

# define X		0
# define Y		1

# define NRTH_TEXT	2
# define STH_TEXT	3
# define EST_TEXT	4
# define WST_TEXT	5

# define NORTH		6
# define SOUTH		7
# define EAST		8
# define WEST		9

# define SPEED		0.1
# define ROTATIONSPEED		0.05


//*------------------------------//
//	  * KEYBOARD SETTINGS *.     //
//*------------------------------*//
# define KEY_PRESS		2
# define KEY_RELEASE		3

/* Clicking on the RED cross on the window frame */
# define KEY_EXIT		17

# define KEY_ESC			65307

# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100
# define KEY_UP				126
# define KEY_LEFT			65361
# define KEY_RIGHT			65363


typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		bits;
	int		len;
	int		endian;
	int		h;
	int		w;
}	t_img;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*address;
	char			*map_file;
	char			*line;
	char			coord;
	char			**d_map;
	int				**map;
	int				rows_map;
	int				cols_map;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	int				bitpp;
	double			vision;
	int				endian;
	int				lengh_line;
	int				line_height;
	int				d_start;
	int				d_end;
	int				x_axys;
	int				y_axys;
	int				textwallx;
	int				textwally;
	int				size;
	int				move_keys;
	int				rotate_keys;
	int				side_keys;
	int				hit_side;
	int				turn_dir;
	double			pp_to_wall;
	unsigned int	c;
	unsigned int	f;
	t_vector		vect;
	t_vector		dir;
	t_vector		plane;
	t_vector		rays;
	t_vector		distance;
	t_vector		dis_wall;
	double			rotation;
	t_img			img_data;
	t_img			n_img;
	t_img			s_img;
	t_img			e_img;
	t_img			w_img;
}	t_game;

//*===SETTINGS COLORS===*//
//*===Color font code===*//
# define BLACK   "\x1B[30m"
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1B[37m"
# define ORANGE  "\x1B[38;2;255;128;0m"
# define ROSE    "\x1B[38;2;255;151;203m"
# define LBLUE   "\x1B[38;2;53;149;240m"
# define LGREEN  "\x1B[38;2;17;245;120m"
# define GRAY    "\x1B[38;2;176;174;174m"
//*===Color background code===*//
# define BG_BLACK   "\x1B[40m"
# define BG_RED     "\x1B[41m"
# define BG_GREEN   "\x1B[42m"
# define BG_YELLOW  "\x1B[43m"
# define BG_BLUE    "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN    "\x1B[46m"
# define BG_WHITE   "\x1B[47m"
# define BG_ORANGE  "\x1B[48;2;255;128;0m"
# define BG_LBLUE   "\x1B[48;2;53;149;240m"
# define BG_LGREEN  "\x1B[48;2;17;245;120m"
# define BG_GRAY    "\x1B[48;2;176;174;174m"
# define BG_ROSE    "\x1B[48;2;255;151;203m"

# define RESET   "\x1b[0m"

//*===MAP===*//
void			skip_spaces(char *str, int *i);
void			ft_check_access(char *path);
int				check_extension(char *str, char *ext);
void			ft_check_comp(t_game *game);
void			ft_check_borders(t_game *game);
void 			ft_check_textures(t_game *game);
char			*read_and_stash(int fd, char *stash);
void			alloc_map_mem(t_game *game);
void			update_x_direction(t_game *game);
void			ft_read_file(t_game *game, char *file);
void			ft_process_map(t_game *game);
void			fill(t_game *game, int size, int current, int col);
unsigned int	*ft_ctoascii(char **num);
void 			ft_load_texture(t_game *g, int i, int j, char *dir);
void 			ft_load_color(t_game *game, int i, int *j, char color);

//*===GAME===*//
int				close_game(t_game *game);
t_img			init_img(t_game *game, char *path);
int				keypress(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			ft_algorithm(t_game *game);
void			ft_ray_line(t_game *game, int i);
void			update_textures(t_game *game, int i);
int				ft_raycasting(t_game *game);
void			ft_data_text(t_game *game);
double			player_distance(double ray);
void			ft_wall_dist(t_game *game);

//*===MESSAGES===*//
void			error_message(char *msg);
void			exit_message(char *msg, t_game *game);


#endif