#include "../philo.h"

void *keeper(void *info)
{
	t_args *args;
	int i;
	int status;

	args = (t_args *)info;
	status = -1;
	while (status)
	{
		i = 0;
		while (i < args->num_of_philos)
		{
			if ((args->time_to_die / 1000) - get_timestamp(args->tinfo[i].last_meal) < 0)
			{
				// printf("DEAD ST %ld\n", get_timestamp(args->tinfo[i].last_meal) - (args->time_to_die / 1000));
				args->status = DEAD;
				status = 0;
				print_state(&(args->tinfo[i]), DEAD);
				break ;
				// completion(args);
			}	
			i++;
		}
	}
	return NULL;
}