# Meta

NAME := qub3D

SRCDIR := ./src
OBJDIR := ./obj

SRC :=\
	main.c \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

ARCH := $(shell uname)

# MiniLibX

MLX_DIR := ./lib/minilibx-opengl
MLX_AR := $(MLX_DIR)/libmlx.a
ifeq ($(ARCH), Linux)
	MLX_LD := -lXext -lX11 -L$(MLX_DIR) -lmlx 
else
	MLX_LD := -lmlx -framework OpenGL -framework AppKit
endif

# Libft

FT_DIR := ./lib/libft
FT_AR := $(FT_DIR)/libft.a
FT_LD := -L ./lib/libft -lft

# Compilation and linking

CC := cc
INCLUDE := -I$(MLX_DIR) -I$(FT_DIR) -I$(SRCDIR)
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
