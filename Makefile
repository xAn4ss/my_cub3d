INC=%%%%

INCLIB=$(INC)/../lib

NAME= cub3D

SRC = main.c data_checker.c get_next_line.c\
		get_next_line_utils.c utiles.c\
		map_check.c Sources/cub3d.c Sources/move_manager.c\
		Sources/raycasting.c Sources/drawing_functions.c Sources/init_data.c\

LFLAGS = -L../minilibx-linux-master -lmlx -L$(INCLIB) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) $(LFLAGS) Libft/libft.a -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
# -L../minilibx-linux -lmlx -L$(INCLIB) -lXext -lX11 -lm
# -lmlx -framework OpenGL -framework AppKit