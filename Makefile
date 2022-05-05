NAME = philo

HEADER = philo.h 

LIST_C = main.c time.c check_get_args.c ft_atoi.c ft_strchr.c \
		start_threads.c keeper.c routine.c

OBJ_C = ${patsubst %.c, ${OBJ}%.o, ${LIST_C}}

FLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread

SRC = src/
OBJ = obj/

GREEN = \033[0;32m
NC = \033[0m

all : ${NAME}
	@echo "<<<< DONE ! >>>>"

${NAME} : ${OBJ_C} ${OBJ}
	@gcc -o ${NAME} ${FLAGS} ${PTHREAD} ${OBJ_C}

${OBJ}%.o : ${SRC}%.c ${HEADER}
	@mkdir -p ${OBJ}
	@gcc ${FLAGS} -c $< -o $@

clean :
	@rm -rf ${OBJ_C} ${OBJ}
	@echo "object files was deleted"

fclean : clean
	@rm -f ${NAME}
	@echo "${NAME} was deleted"

re : fclean all

.PHONY : all clean fclean re 