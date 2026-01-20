NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f
UNAME		:= $(shell uname)

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT		= Libft
LIBFT_A		= $(LIBFT)/libft.a

# OS-dependent MiniLibX setup
ifeq ($(UNAME), Linux)
	MLX_DIR		= mlx/minilibx-linux
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

ifeq ($(UNAME), Darwin)
	MLX_DIR		= mlx/minilibx-macos
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

MLX_A		= $(MLX_DIR)/libmlx.a

# Source files
SRC			= \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/parser.c \
			$(SRC_DIR)/parser_helpers.c \
			$(SRC_DIR)/validation.c \
			$(SRC_DIR)/validation_helpers.c
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Include paths
INCLUDES	= -I$(INC_DIR) -I$(LIBFT) -I$(MLX_DIR)

# ------------------------------- RULES -------------------------------------- #

# Default rule
all: $(NAME)

# Main executable
$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) -LLibft -lft $(MLX_FLAGS) -o $(NAME)

# Object files directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile Libft
$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

# Compile MiniLibX
$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

# Object compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files and Libft objects
clean:
	$(MAKE) clean -C $(LIBFT)
	$(RM) -r $(OBJ_DIR)

# Full clean including executable and Libft
fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Bonus rule (even if bonus not implemented yet)
bonus: all

# Phony targets
.PHONY: all clean fclean re bonus
