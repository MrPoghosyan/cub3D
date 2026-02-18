# ----------------------------- PROJECT SETTINGS ----------------------------- #
NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

RM          = rm -f
UNAME       := $(shell uname)

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

LIBFT_DIR   = Libft
LIBFT_A     = $(LIBFT_DIR)/libft.a
INC_DIR		= include
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ----------------------------- OS-dependent MiniLibX ----------------------- #
ifeq ($(UNAME), Linux)
    MLX_DIR     = mlx/minilibx-linux
    MLX_A       = $(MLX_DIR)/libmlx.a
    MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
endif

ifeq ($(UNAME), Darwin)
    MLX_DIR     = mlx/minilibx-macos
    MLX_A       = $(MLX_DIR)/libmlx.a
    MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# ----------------------------- SOURCES & OBJECTS ---------------------------- #
# Source files
SRC			= \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/assets/error.c \
			$(SRC_DIR)/assets/free.c \
			$(SRC_DIR)/assets/validation.c \
			$(SRC_DIR)/assets/validation_helpers.c \
			$(SRC_DIR)/assets/utils.c \
			$(SRC_DIR)/parser/parser.c \
			$(SRC_DIR)/parser/parser_help.c \
			$(SRC_DIR)/parser/parser_helpers.c \
			$(SRC_DIR)/engine/engine.c \
			$(SRC_DIR)/engine/hooks.c \
			$(SRC_DIR)/engine/init.c \
			$(SRC_DIR)/engine/movement.c \
			$(SRC_DIR)/render/render.c \
			$(SRC_DIR)/render/render_texture.c \
			$(SRC_DIR)/render/render_utils.c \
			$(SRC_DIR)/texture/texture_load.c \
			$(SRC_DIR)/texture/texture_utils.c

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ----------------------------- RULES ---------------------------------------- #

all: mlx_libft mlx_mlx $(NAME)

# Build Libft
mlx_libft:
	$(MAKE) -C $(LIBFT_DIR)

# Build MiniLibX
mlx_mlx:
	$(MAKE) -C $(MLX_DIR)

# Build executable
$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) -LLibft -lft $(MLX_FLAGS) -o $(NAME)

# Ensure object directory exists
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files and Libft objects
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) -r $(OBJ_DIR)

# Full clean including executable and Libft
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Bonus rule placeholder
bonus: all
.PHONY: all clean fclean re bonus mlx_libft mlx_mlx
