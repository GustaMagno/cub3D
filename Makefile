NAME = cub3D
ARG = map.cub

CC = cc
GCC = gcc
CFLAGS = -Wall -Wextra -Werror
GFLAGS = -Wall -Wextra -Werror -g3 -O0
VALGRIND = valgrind \
			--leak-check=full \
			--track-fds=yes \
			--show-leak-kinds=all \
			--track-origins=yes \

RM = rm -rf
BUILD_DIR = build
MLX_DIR = external/mlx
LIBFT_DIR = external/libft
INCLUDES = -I. -I./includes -I$(MLX_DIR)

all: $(NAME)

SRCS = cub3D.c \
		src/parse/data_structure.c \
		src/parse/parse.c \
		src/parse/parse_utils.c \
		src/parse/map.c \
		src/parse/map_utils.c \
		src/utils/allocation_free.c \
		src/utils/allocation.c \
		src/utils/get_next_line.c \
		src/utils/string_advanced.c \
		src/utils/string_basic.c \
		src/utils/print.c \
		src/utils/clean_data.c \
		src/utils/is_something.c \
		src/exec/mlx_exec.c \
		src/exec/end_mlx.c \
		src/exec/game_loop.c \
		src/exec/create_map.c \
		src/utils/ft_calloc.c \

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
	$(MAKE) CC=$(GCC) CFLAGS="$(GFLAGS)" all
	$(VALGRIND) ./$(NAME) $(ARG)

re3:
	$(MAKE) fclean
	-$(MAKE) mlx
	$(MAKE) libft
	$(MAKE) CC=$(GCC) CFLAGS="$(GFLAGS)" all
	$(VALGRIND) ./$(NAME) $(ARG)

.PHONY: all clean fclean re mlx externalre val valchild val3 re3
