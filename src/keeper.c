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
			if (args->tinfo[i].status == 10 || args->tinfo[i].status == 11)
				// printf("T%zd #%d st %d\n", get_timestamp(args->tinfo[i].start_time), args->tinfo[i].thread_num, args->tinfo[i].status);
			if (args->tinfo[i].status == 9)
				// printf("T%zd #%d st %d\n", get_timestamp(args->tinfo[i].start_time), args->tinfo[i].thread_num, args->tinfo[i].status);
			if (args->tinfo[i].status == 0)
				status = 0;
			// printf("i %d\n", i);
			i++;
			
		}
	}
	return NULL;
}