MAKEFLAGS += --silent
CC = cc
LIBFT_PATH = Libft/
LIB = -L${LIBFT_PATH} -lft
LIBFT = libft.a
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c commands.c commands2.c commands3.c check.c check2.c \
	pre_parsing.c pre_parsing2.c parsing.c utils.c utils2.c
OBJS_EXEC = ${SRCS:.c=.o}
EXEC = minishell


all: ${EXEC}
	echo "\033[7;32m~| Tous les fichiers sont à jour ! |~\033[0m"\

${LIBFT}:
	@make -sC ${LIBFT_PATH} all \
                && echo "\033[1;32m~| Compilation de la lib : OK |~\033[0m"\
                || echo "\033[1;31m~| Compilation de la lib : Erreur |~\033[0m"

${EXEC}: ${LIBFT} ${OBJS_EXEC}
	${CC} ${CFLAGS} -lreadline -I ./minishell.h ${OBJS_EXEC} ${LIB} -o ${EXEC} \
		&& echo "\033[1;32m~| Compilation du $@ : OK |~\033[0m"\
		|| echo "\033[1;31m~| Compilation du $@ : Erreur |~\033[0m"

clean:
	make -sC ${LIBFT_PATH} fclean
	rm -f ${OBJS_BONUS}
	rm -f ${OBJS_EXEC}\
		&& echo "\033[1;33m~| Nettoyage des .o : OK |~\033[0m"\
		|| echo "\033[0;31m~| Compilation du $@ : Erreur |~\033[0m"

fclean: clean
	rm -f ${BONUS}
	rm -f ${EXEC} \
		&& echo "\033[1;33m~| Nettoyage des executables : OK |~\033[0m"\
		|| echo "\033[0;31m~| Compilation du $@ : Erreur |~\033[0m"

re: fclean all
