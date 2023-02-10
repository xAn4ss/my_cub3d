INC=%%%%

INCLIB=$(INC)/../lib

NAME= cub3D

SRC = main.c data_checker.c data_checker_2.c get_next_line.c\
		map_check_2.c get_next_line_utils.c utiles.c utiles_2.c\
		map_check.c Sources/cub3d.c Sources/move_manager.c\
		Sources/raycasting.c Sources/drawing_functions.c Sources/init_data.c\

LFLAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) $(LFLAGS) Libft/libft.a -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
# -L../minilibx-linux -lmlx -L$(INCLIB) -lXext -lX11 -lm
# -lmlx -framework OpenGL -framework AppKit
