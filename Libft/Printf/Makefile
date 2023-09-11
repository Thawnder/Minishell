NAME = libftprintf.a

GCC = gcc

SRC = ft_printf.c \
      ft_putsth.c \
      ft_libft.c \
      ft_flags_util.c \
      ft_flags.c \
      ft_flags2.c \
      ft_flags3.c \
      ft_flags4.c \
      ft_flags5.c \
      ft_gpasdeplace.c \

FLAGS = -Wall -Wextra -Werror -g

OBJ = ${SRC:.c=.o}

all: ${NAME}

.c.o:
	${GCC} ${FLAGS} -I ./ -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	ar rc ${NAME} ${OBJ}

bonus: all

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
