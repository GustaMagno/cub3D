# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 19:46:45 by otlacerd          #+#    #+#              #
#    Updated: 2026/04/13 19:52:52 by otlacerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
BUILD_DIR = build
MLX_DIR = minilibx-linux
INCLUDES = -I. -I./includes -I$(MLX_DIR)

all: $(NAME)

SRCS = cub3D.c \

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
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
