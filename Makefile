NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = *.c
OBJ = $(SRC:.c=.o)
FT_LNK = -L ./libft -lft

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(FT_LNK) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re:	fclean all