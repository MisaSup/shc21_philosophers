NAME = philo

HEADER = philo.h 

# LIST_C = main.c  exit_psw.c start_sort.c check_number.c\
# double_linked_list.c swap.c push.c rotate.c reverser.c \
# min_max.c base_case.c double_linked_list2.c check_get_args.c\
# redux_sort.c  ft_strncmp.c ft_split_ex.c\

LIST_C = main.c time.c check_get_args.c ft_atoi.c ft_strchr.c start_threads.c keeper.c

OBJ_C = ${patsubst %.c, ${OBJ}%.o, ${LIST_C}}

FLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread

SRC = src/
OBJ = obj/

GREEN = \033[0;32m
NC = \033[0m

all : ${NAME}
	@echo "${GREEN}DONE !${NC}"

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