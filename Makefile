# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 19:46:45 by otlacerd          #+#    #+#              #
#    Updated: 2026/04/19 10:29:35 by otlacerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
GCC = gcc
CFLAGS = -Wall -Wextra -Werror
GFLAGS = -Wall -Wextra -Werror -g3 -O0
VALGRIND = valgrind \
			--leak-check=full \
			--track-fds=yes \
			--show-leak-kinds=all \
			--track-origins=yes \
			--suppressions=readline.supp
CHILDREN = --child-silent-after-fork=no \
			--trace-children=yes
RM = rm -rf
BUILD_DIR = build
MLX_DIR = external/mlx
LIBFT_DIR = external/libft
INCLUDES = -I. -I./includes -I$(MLX_DIR)

all: $(NAME)

SRCS = cub3D.c \
		src/parse/data_struct.c \
		src/parse/parse.c \
		src/parse/parse_utils.c \
		src/general_utils/allocation_free.c \
		src/general_utils/allocation.c \
		src/general_utils/get_next_line.c \
		src/general_utils/string_advanced.c \
		src/general_utils/string_basic.c \
		src/general_utils/print.c \
		src/general_utils/data.c \
		src/general_utils/is_something.c \

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

$(NAME): $(OBJS)
	@if [ -d "$(LIBFT_DIR)" ]; then \
			$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -o $(NAME); \
	else \
		$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME); \
	fi

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@cd $(MLX_DIR) && ./configure
	@$(MAKE) -C $(MLX_DIR) -f makefile.gen
	@cp -f $(MLX_DIR)/mlx.h ./includes/

libft:
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR); \
	fi	

externalre: fclean mlx

clean:
	@rm -f $(OBJS)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi

fclean: clean
	@rm -f $(NAME)
	@rm -Rf $(BUILD_DIR)
	@rm -Rf $(MLX_DIR)
	@rm -Rf $(LIBFT_DIR)

re: fclean mlx libft all

val: $(NAME)
	$(VALGRIND) ./$(NAME)

valchild: $(NAME)
	$(VALGRIND) $(CHILDREN) ./$(NAME)

val3:
	$(MAKE) CC=$(GCC) CFLAGS="$(GFLAGS)"
	$(VALGRIND) ./$(NAME)

re3:
	$(MAKE) fclean
	$(MAKE) CC=$(GCC) CFLAGS="$(GFLAGS)" all
	$(VALGRIND) ./$(NAME)

.PHONY: all clean fclean re mlx externalre val valchild val3 re3
