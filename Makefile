# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 19:46:45 by otlacerd          #+#    #+#              #
#    Updated: 2026/04/20 16:56:12 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -O3 #-Wall -Wextra -Werror
RM = rm -rf
BUILD_DIR = build
MLX_DIR = minilibx-linux/
INCLUDES = -I. -I./includes -I$(MLX_DIR)

all: mlx $(NAME)

SRCS = cub3D.c \
	src/exec/mlx_exec.c \
	src/exec/end_mlx.c \
	src/exec/game_loop.c \
	src/exec/create_map.c \
	src/parsing/data_struct.c \
	utils/ft_calloc.c \

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

$(MLX_DIR)/libmlx.a:
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX_DIR)/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	echo $(MLX_DIR)
	$(RM) $(NAME)
	$(RM) $(MLX_DIR)
	$(RM) libmlx.a
	$(RM) includes/mlx.h

re: fclean all

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone git@github.com:42paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)
# 	@cp $(MLX_DIR)/libmlx.a
	@cp $(MLX_DIR)/mlx.h ./includes

.PHONY: all clean fclean re
