#include "../philo.h"

void *keeper(void *info)
{
	t_args *args;
	int i;

	args = (t_args *)info;
	while (1)
	{
		i = 0;
		while (i < args->num_of_philos)
		{
			if (args->time_to_die - get_timestamp(args->tinfo[i].last_meal) < 0)
			{
				args->status = DEAD;
				print_state(&(args->tinfo[i]), DEAD);
			}	
			i++;
		}
		if (args->status == DEAD || args->status == DONE)
			break ;
	}
	if (args->status == DEAD)
		pthread_mutex_unlock(&(args->dead_mutex));
	return NULL;
}