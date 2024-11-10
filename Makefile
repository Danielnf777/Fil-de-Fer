NAME = fdf

SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

FLAGS = -g -Wall -Wextra -Werror -fsanitize=address

CC = cc

LIBFT = /home/danavarr/Documents/libft

all : $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) ../libft/libft.a  ./minilibx-linux/libmlx.a -I./minilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz -o $(NAME)


%.o: %.c fdf.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
