# Meta

NAME := minirt

ifeq ($(OS), Windows_NT)
	ARCH := Windows
else
	ARCH := $(shell uname -s)
endif

SRCDIR := ./src
OBJDIR := ./obj

APP_DIR := app
APP_SRC :=\
	app.c \

WINDOW_DIR := window
WINDOW_SRC :=\
	window.c \

INPUT_DIR := input
INPUT_SRC :=\
	input.c \

SCENE_DIR := scene
SCENE_SRC :=\
	ecs.c \

SRC :=\
	main.c \
	$(APP_SRC:%=$(APP_DIR)/%) \
	$(WINDOW_SRC:%=$(WINDOW_DIR)/%) \
	$(INPUT_SRC:%=$(INPUT_DIR)/%) \
	$(SCENE_SRC:%=$(SCENE_DIR)/%) \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

# MiniLibX

MLX_DIR := ./lib/mlx42
MLX_AR := $(MLX_DIR)/build/libmlx42.a
MLX_LD := -L $(MLX_DIR)/build -lmlx42

ifeq ($(ARCH), Linux)
	MLX_LD += -ldl -lglfw3 -pthread -lm
else ifeq ($(ARCH), Windows)
	MLX_LD += -lglfw3 -lopengl32 -lgdi32
else ifeq ($(ARCH), Darwin)
	MLX_LD += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

# Libft

FT_DIR := ./lib/libft
FT_AR := $(FT_DIR)/libft.a
FT_LD := -L ./lib/libft -lft

# Compilation and linking

CC := cc
INCLUDE := -I$(MLX_DIR)/include -I$(FT_DIR) -I$(FT_DIR)/include -I$(SRCDIR)
CFLAGS := -Wall -Werror -Wextra $(INCLUDE)
LDFLAGS := -lm $(MLX_LD) $(FT_LD) 

# Rules

all: $(NAME)

debug: CFLAGS+= -g -fsanitize=address,undefined
debug: LDFLAGS+= -g -fsanitize=address,undefined
debug: $(NAME)

$(NAME): $(MLX_AR) $(FT_AR) $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

$(MLX_AR):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(FT_AR):
	@$(MAKE) -C $(FT_DIR)

# Include dependency info
-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	@$(CC) $(CFLAGS) -MMD -c $< -o $@ 

clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(FT_DIR)
	@/bin/rm -rf $(MLX_DIR)/build
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
