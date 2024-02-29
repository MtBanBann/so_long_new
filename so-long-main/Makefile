
NAME := so_long
SRC_DIR := src
BUILD_DIR := .build
DEPS_DIR := .deps
INC := inc/so_long.h \
		/home/kali/Desktop/minilibx-linux/mlx.h

SO_LONG =	$(SRC_DIR)/so_long.c \
			$(SRC_DIR)/map_test.c \
			$(SRC_DIR)/map_good.c 

SRC := $(SO_LONG)

OBJS    := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEPS    := $(patsubst %.o, %.d,$(OBJS))

LIBS       				:= libft 

LIBS_TARGET 			:= libft/libft.a 

DIR_MLX		:=	minilibx_linux

MLX_TARGET :=			minilibx-linux/libmlx_Linux.a 

CC := cc -g3
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS := $(addprefix -L,$(dir $(LIBS_TARGET))) \
			 $(addprefix -L,$(dir $(MLX_TARGET)))

LDLIBS := -lmlx_Linux -lft -lX11 -lXext  -lm 

RM := rm -f

all: $(NAME) 

force:


$(LIBS_TARGET): force
	@$(MAKE) -C $(@D) --no-print-directory

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

$(NAME): $(OBJS) $(LIBS_TARGET)
			$(CC) $(LDFLAGS) $(OBJS)  $(LDLIBS) -o $(NAME) 

-include $(DEPS)
# **************************************************************************** #
CLEAN_DIRS := libft/
clean:
	$(MAKE) -C $(CLEAN_DIRS) clean
	$(RM) -r $(BUILD_DIR) $(DEPS_DIR)
# **************************************************************************** #
fclean:
	$(MAKE) -C $(CLEAN_DIRS) fclean
	$(RM) -r $(BUILD_DIR) $(DEPS_DIR) $(NAME) $(BONUS)
# **************************************************************************** #
re: fclean all
# **************************************************************************** # # .PHONY #
.PHONY: all clean fclean re
# *****************************