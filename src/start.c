#include "../philo.h"
#include "ft_atoi.c"
#include "ft_strchr.c"
#include "../philo.h"
#include "check_get_args.c"

void set_start_values(t_args *args)
{
	args->num_of_philos = -1;
	args->time_to_die = -1;
	args->time_to_eat = -1;
	args->time_to_sleep = -1;
	args->meal_counter = -1;
}

int main(int argc, char const *argv[])
{
	t_args	arguments;

	set_start_values(&arguments);
	get_check_args(argc - 1, (char **)argv + 1, &arguments);
	printf("%d %d %d %d %d\n", arguments.num_of_philos, arguments.time_to_die, arguments.time_to_eat,
	arguments.time_to_sleep, arguments.meal_counter);
	return 0;
}
