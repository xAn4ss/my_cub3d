
INC=%%%%

INCLIB=$(INC)/../lib

NAME= kyub

SRC = main.c data_checker.c get_next_line.c\
		get_next_line_utils.c utiles.c\
		cub3d.c

LFLAGS = -L../minilibx-linux-master -lmlx -L$(INCLIB) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(SRC)
	$(CC) -o $(NAME) $(SRC) $(LFLAGS) Libft/libft.a

clean:
	rm -f $(NAME) $(OBJ)

re: clean all
