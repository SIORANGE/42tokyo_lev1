NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCFILE = ft_printf.c utils.c treat_converter.c printer.c

OBJECTS = $(SRCFILE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
