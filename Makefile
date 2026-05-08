CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = miniRT
NAME_H = main.h
SRC = main.c \
			Initialization/data_checker.c \
			Initialization/data_checker_vectors.c \
			Initialization/initializers.c \
			Initialization/parse_alc.c \
			Initialization/parse_counters.c \
			Initialization/parse_objects.c \
			Initialization/parse_utils.c \
			Initialization/parser.c \
			Utils/free_memory.c \
			Utils/linear_math.c \
			Utils/linear_math_2.c \
			Utils/memory_handler.c \
			Rays/apply_ray.c \
			Rays/ray_math.c \
			Rays/ray_math_cylinder.c \
			Light/lights.c \
			Light/lights_utils.c \
			Light/shadows.c \
			utils.c \

OBJ = $(SRC:.c=.o)

LIBFT = Libft_power
LIBFT_A = Libft_power/libft.a

MLX = minilibx-linux
MLX_A = minilibx-linux/libmlx.a

INCLUDES = -I Libft_power/ -I Libft_power/ft_printf/ -I Libft_power/get_next_line/ -I minilibx-linux
MLX_LIB = -Lminilibx-linux -lmlx_Linux -L/usr/lib/X11 -lX11 -lXext -lm -lz

LINKERS = -lm

all: $(NAME)

############# Linking phase - creating the executable
############# Linkers are needed to link libraries
############# Example:

# $(NAME): $(OBJ) $(LIBFT_A)
# 	$(CC) $(OBJ) $(LIBFT_A) -o $(NAME) $(LINKERS)
$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBFT_A) -o $(NAME) $(LINKERS)

$(LIBFT_A):
	make -C $(LIBFT)

$(MLX_A):
	make -C $(MLX)

############# COMPILE FILES
############# Inlcude flags are meant for folders (Like LIBFT or PRITNF)
############# Example:
# %.o: %.c $(NAME_H)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c $(NAME_H)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f $(OBJ)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean
	make -C $(MLX) clean

re: fclean all

.PHONY: all clean fclean re
