NAME := libft.a

SRCDIR := ./src
OBJDIR := ./obj
INCDIR := ./include

BUF_DIR := buf
BUF_SRC :=\
	buf.c\
	buf_io.c\

STD_DIR := std
STD_SRC :=\
	ft_atof.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_itoa.c \

CSTR_DIR := cstr
CSTR_SRC :=\
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_bzero.c \
	ft_split.c \
	ft_striteri.c \
	ft_strmapi.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strflds.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strarr_del.c\
	ft_strtrim.c \
	ft_substr.c \
	ft_toklen.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \

IO_DIR := io
IO_SRC :=\
	get_next_line.c \
	ft_printf.c \
	ft_putbase.c \
	ft_puthex.c \
	ft_putdec.c \
	ft_putptr.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \

LIST_DIR := list
LIST_SRC :=\
	ft_lstnew.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \

MATH_DIR := math
MATH_SRC :=\
	math.c \
	max.c \
	min.c \
	float2.c \
	float2_transform.c \
	float2_rotation.c \
	float3.c \
	float3_transform.c \
	float3_rotation.c \
	float4x4.c \
	float4x4_transform.c \

SRC :=\
	$(BUF_SRC:%=$(BUF_DIR)/%)   \
	$(STD_SRC:%=$(STD_DIR)/%)   \
	$(CSTR_SRC:%=$(CSTR_DIR)/%) \
	$(IO_SRC:%=$(IO_DIR)/%)     \
	$(LIST_SRC:%=$(LIST_DIR)/%) \
	$(MATH_SRC:%=$(MATH_DIR)/%) \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=.d)

CC := cc
CFLAGS := -O3 -I$(INCDIR) -I./ -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rus $(NAME) $(OBJ)

# Include dependency info
-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(CFLAGS) -MMD -c $< -o $@ 

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all so clean fclean re bonus
