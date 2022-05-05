#include "../philo.h"

void completion(t_args *arguments)
{
    int i;

    i = -1;
    while (++i < arguments->num_of_philos)
        pthread_mutex_destroy(&(arguments->tinfo->forks[i]));
    free(arguments->tinfo->forks);
    free(arguments->tinfo);
}

int main(int argc, char *argv[])
{
    t_args arguments;
         
    get_check_args(argc - 1, argv + 1, &arguments);
    init_threads(&arguments);
    completion(&arguments);
    return (0);
}

