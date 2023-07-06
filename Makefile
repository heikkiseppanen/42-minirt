# Meta

NAME := qub3D

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

SRC :=\
	main.c \
	$(APP_SRC:%=$(APP_DIR)/%) \
	$(WINDOW_SRC:%=$(WINDOW_DIR)/%) \
	$(INPUT_SRC:%=$(INPUT_DIR)/%) \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

ARCH := $(shell uname)

# MiniLibX

ifeq ($(ARCH), Linux)
	MLX_DIR := ./lib/minilibx-linux
	MLX_AR := $(MLX_DIR)/libmlx.a
	MLX_LD := -lXext -lX11 -L$(MLX_DIR) -lmlx 
else
	MLX_DIR := /usr/local/include
	MLX_AR := /usr/local/lib/libmlx.a
	MLX_LD := -lmlx -framework OpenGL -framework AppKit
endif

# Libft

FT_DIR := ./lib/libft
FT_AR := $(FT_DIR)/libft.a
FT_LD := -L ./lib/libft -lft

# Compilation and linking

CC := cc
INCLUDE := -I$(MLX_DIR) -I$(FT_DIR) -I$(FT_DIR)/include -I$(SRCDIR)
CFLAGS := -march=native -O2 -Wall -Werror -Wextra $(INCLUDE)
LDFLAGS := -lm $(MLX_LD) $(FT_LD) 

# Rules

all: $(NAME)

$(NAME): $(MLX_AR) $(FT_AR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

$(MLX_AR):
	$(MAKE) -C $(MLX_DIR)

$(FT_AR):
	$(MAKE) -C $(FT_DIR)

# Include dependency info
-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(CFLAGS) -MMD -c $< -o $@ 

clean:
	/bin/rm -rf $(OBJDIR)
ifeq ($ARCH, Linux)
	make clean -C $(MLX_DIR)
endif

fclean: clean
	make fclean -C $(FT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all so clean fclean re
