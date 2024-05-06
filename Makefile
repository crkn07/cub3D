# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 18:29:30 by crtorres          #+#    #+#              #
#    Updated: 2024/05/06 13:52:49 by crtorres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC_PATH = ./src
DOT_O = _Objfiles

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
MINILIBX = -framework OpenGL -framework AppKit
LIBFT = ./src/libft/libft.a
MLX = ./mlx/libmlx.a

LIB = cub3d.h

SRC = ft_cub3d.c\
		ft_error.c\
		ft_check_map.c\
		ft_check_map_comp.c\
		ft_functions_utils.c\
		ft_map_utils.c\
		ft_move_keys.c\
		ft_read_file.c\
		ft_smaller_mlx.c\
		ft_dda.c\
		ft_dda_utils.c\

OBJ = $(addprefix $(DOT_O)/, $(SRC:%.c=%.o))

all: make_libft make_mlx $(DOT_O) $(NAME)

$(DOT_O):
	mkdir -p $(DOT_O)

$(DOT_O)/%.o: $(SRC_PATH)/%.c | $(DOT_O)
	$(PURPLE) COMPILING MINISHELL... $(RESET)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

make_libft:
	@make all -sC ./src/libft

make_mlx:
	@make -C ./mlx
	
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -I $(LIB) $(LIBFT) $(MLX) $(MINILIBX) -o $(NAME)
	$(GREEN)
	@clear
	@echo "CUB3D READY!"
	@echo $(RESET)
	
clean:
	$(CYAN) "\n cleaning everything...\n" $(RESET)
	@rm -f $(OBJ)
	@make fclean -sC ./src/libft
	@make clean -C ./mlx
	@rm -rf $(DOT_O)

fclean: clean
	@clear
	@rm -f $(NAME)
	@make fclean -sC ./src/libft
	@make clean -C ./mlx
	@rm -rf $(DOT_O)

re: fclean all

GREEN 	= @echo "\033[0;32m"
BLUE 	= @echo "\033[0;34m"
PURPLE 	= @echo "\033[0;35m"
CYAN 	= @echo "\033[0;36m"
YELLOW = \033[0;93m
RESET 	= "\033[1;0m"

.PHONY:		all clean fclean re